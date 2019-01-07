#ifndef CROMBIE2_JOB_H
#define CROMBIE2_JOB_H


#include <vector>

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
         const std::string& file_name);

    void add_analyzer (Analyzer* analyzer);
    void run ();

    const FileGroup& get_group () const;
    const FileEntry& get_entry () const;

  private:

    FileGroup& group;
    FileEntry& entry;

    std::vector<Analyzer*> analyzers;
    Tree tree;

  };
}


#endif
