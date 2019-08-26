#! /usr/bin/env perl

use strict;
use warnings;

foreach my $infile (@ARGV) {
    my @lines;
    open (my $handle, '<', $infile);
    push @lines, <$handle>;
    close $handle;

    for (@lines) {
        if (m|crombie2/(\w+)\.h|) {
            if (! grep { /$1[^\.]/ } @lines) {
                print "$infile doesn't need $_\n";
            }
        }
    }
}
