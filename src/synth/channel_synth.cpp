#include "synth/channel_synth.h"

#include "dfg/dfg.h"

#include <set>

using std::set;

namespace synth {

void ChannelSynth::ResolveChannels(DModule *root_mod) {
  ChannelSynth synth;
  synth.ExtractChannels(root_mod);
  synth.ConnectChannels();
}

void ChannelSynth::ConnectChannels() {
  for (auto &p : channel_infos_) {
    ChannelInfo &c = p.second;
    if (c.reader_channel != NULL && c.writer_channel != NULL) {
      ConnectInternal(c);
    } else {
      ConnectExternal(c);
    }
  }
}

void ChannelSynth::ConnectInternal(ChannelInfo &ci) {
  // find the common parent.
  set<DModule *> reader_parents_set;
  for (DModule *p = ci.reader_channel->reader_module_->parent_mod_;
       p != NULL; p = p->parent_mod_) {
    reader_parents_set.insert(p);
  }
  DModule *common_parent = NULL;
  for (DModule *p = ci.writer_channel->writer_module_->parent_mod_;
       p != NULL; p = p->parent_mod_) {
    if (reader_parents_set.find(p) != reader_parents_set.end()) {
      common_parent = p;
      break;
    }
  }
  CHECK(common_parent);
  DChannel *dchan = DModuleUtil::CreateChannel(common_parent, ci.data_width);
  dchan->channel_name_ = ci.reader_channel->channel_name_;
  dchan->writer_module_ = ci.writer_channel->writer_module_;
  dchan->reader_module_ = ci.reader_channel->reader_module_;
  dchan->is_root_or_source_ = true;
  // Supports just 1 level between the root.
}

void ChannelSynth::ConnectExternal(ChannelInfo &ci) {
  string name;
  DModule *p;
  if (ci.reader_channel == NULL) {
    name = ci.writer_channel->channel_name_;
    p = ci.writer_channel->writer_module_->parent_mod_;
  } else {
    name = ci.reader_channel->channel_name_;
    p = ci.reader_channel->reader_module_->parent_mod_;
  }
  bool first = true;
  for (; p != NULL; p = p->parent_mod_) {
    DChannel *dchan = DModuleUtil::CreateChannel(p, ci.data_width);
    if (first) {
      dchan->is_root_or_source_ = true;
      first = false;
    }
    dchan->channel_name_ = name;
    if (ci.reader_channel != NULL) {
      dchan->reader_module_ = ci.reader_channel->reader_module_;
    } else {
      dchan->writer_module_ = ci.writer_channel->writer_module_;
    }
  }
}

void ChannelSynth::ExtractChannels(DModule *mod) {
  if (mod->graph_) {
    vector<pair<string, int> > r_channels;
    vector<pair<string, int> > w_channels;
    GetChannels(mod->graph_, &r_channels, &w_channels);
    for (size_t i = 0; i < w_channels.size(); ++i) {
      PopulateChannelInfo(w_channels[i].first, true,
			  w_channels[i].second, mod);
    }
    for (size_t i = 0; i < r_channels.size(); ++i) {
      PopulateChannelInfo(r_channels[i].first, false,
			  r_channels[i].second, mod);
    }
  }
  for (size_t i = 0; i < mod->sub_modules_.size(); ++i) {
    ExtractChannels(mod->sub_modules_[i]);
  }
}

void ChannelSynth::PopulateChannelInfo(const string &name, bool is_write,
				       int width, DModule *mod) {
  DChannel *dchan = DModuleUtil::CreateChannel(mod, width);
  dchan->channel_name_ = name;
  if (is_write) {
    dchan->writer_module_ = mod;
    CHECK(channel_infos_[dchan->channel_name_].writer_channel == NULL);
  } else {
    dchan->reader_module_ = mod;
    CHECK(channel_infos_[dchan->channel_name_].reader_channel == NULL);
  }
  ChannelInfo &ci = channel_infos_[dchan->channel_name_];
  if (is_write) {
    ci.writer_channel = dchan;
  } else {
    ci.reader_channel = dchan;
  }
  ci.data_width = width;
}


void ChannelSynth::GetChannels(DGraph *graph,
			       vector<pair<string, int> > *r_channels,
			       vector<pair<string, int> > *w_channels) {
  for (DResource *res : graph->resources_) {
    if (res->opr_->type_ == sym_read_channel) {
      int width = res->output_types_[0]->size_;
      r_channels->push_back(make_pair(res->name_, width));
    }
    if (res->opr_->type_ == sym_write_channel) {
      int width = res->input_types_[0]->size_;
      w_channels->push_back(make_pair(res->name_, width));
    }
  }
}

}  // namespace synth
