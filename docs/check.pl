#! /usr/bin/env perl

use strict;
use warnings;

use Data::Dumper;

foreach my $infile (@ARGV) {
    my @lines;
    open (my $handle, '<', $infile);
    push @lines, <$handle>;
    close $handle;

    my @directly_included;
    my %eventual_included;

    for (@lines) {
        if (m|crombie2/(\w+)\.h|) {
            if (! grep { /$1[^\.]/ } @lines) {
                print "$infile doesn't need $_\n";
            }

            my @tocheck;
            $eventual_included{$1}++;
            push @directly_included, $1;
            push @tocheck, $1;

            while (scalar @tocheck) {
                my $nextfile = pop @tocheck;
                open (my $include_handle, '<', "include/crombie2/$nextfile.h");
                for (<$include_handle>) {
                    if (m|crombie2/(\w+)\.h|) {
                        push @tocheck, $1;
                        $eventual_included{$1}++;
                    }
                }
                close $include_handle;
            }
        }
    }

    for (@directly_included) {
        if ($eventual_included{$_} != 1) {
            print "$infile has $_ included unnecessarily.\n";
            print Dumper(\@directly_included);
            print Dumper(\%eventual_included);
        }
    }
}
