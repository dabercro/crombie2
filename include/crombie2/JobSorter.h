#ifndef CROMBIE2_JOBSORTER_H
#define CROMBIE2_JOBSORTER_H


#include <crombie2/Job.h>


namespace crombie2 {

  class JobSorter {
  public:
    explicit JobSorter (Job& job);
    Job* job;
  };

  bool operator< (const JobSorter& a, const JobSorter& b);

}


#endif
