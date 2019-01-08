#include <crombie2/JobSorter.h>


using namespace crombie2;


JobSorter::JobSorter(Job& job) : job {&job} {}


bool crombie2::operator< (const JobSorter& a, const JobSorter& b) {
  return a.job->size < b.job->size;
}
