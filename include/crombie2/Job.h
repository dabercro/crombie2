#ifndef CROMBIE2_JOB_H
#define CROMBIE2_JOB_H


#include <crombie2/Analyzer.h>
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

    const unsigned long size;

  private:

    const GlobalModel& globalmodel;
    FileGroup& group;
    FileEntry& entry;
    const std::string file_name;

    std::vector<Analyzer*> analyzers;

  };

}


#endif
