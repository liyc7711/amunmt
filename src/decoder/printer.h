#pragma once

#include "god.h"

template <class OStream>
void Printer(const History& history, size_t lineNo, OStream& out) {
  LOG(progress) << "Line " << lineNo
    << " | Best translation: "
    << God::GetTargetVocab()(history.Top().first)
    << " ||| " << history.Top().second->GetCost();
    
  if(God::Get<bool>("n-best-list")) {
    NBestList nbl = history.NBest(God::Get<size_t>("beam-size"));
    for(size_t i = 0; i < nbl.size(); ++i) {
      auto& r = nbl[i];
      out << lineNo << " ||| " << God::GetTargetVocab()(r.first) << " |||";
      for(size_t j = 0; j < r.second->GetCostBreakdown().size(); ++j) {
        out << " F" << j << "= " << r.second->GetCostBreakdown()[j];
      }
      out << " ||| " << r.second->GetCost() << std::endl;
    }
  }
  else {
    out << God::GetTargetVocab()(history.Top().first) << std::endl;
  }
}
