#ifndef CROMBIE2_JOB_H
#define CROMBIE2_JOB_H


#include <crombie2/Analyzer.h>
#include <crombie2/FileEntry.h>
#include <crombie2/FileGroup.h>
#include <crombie2/GlobalModel.h>


namespace crombie2 {
  class Job {
  public:
    Job (const GlobalModel& globalmodel,
         FileGroup& group,
         FileEntry& entry,
         const std::string& file);

    void add_analyzer (Analyzer* analyzer);
    void run ();

    const FileGroup& get_group () const;
    const FileEntry& get_entry () const;

    const std::string& get_file_name () const;

    /// Used for priority setting of jobs
    bool operator< (const Job& other);

  private:

    const GlobalModel& globalmodel;
    FileGroup& group;
    FileEntry& entry;
    const std::string file_name;

    const unsigned long size;

    std::vector<Analyzer*> analyzers;

  };
}


#endif
