#! /usr/bin/env perl

use strict;
use warnings;

use Data::Dumper;

foreach my $infile (@ARGV) {
    my @lines;
    open (my $handle, '<', $infile);
    push @lines, <$handle>;
    close $handle;

    my @directly_included = ();
    my %eventual_included = ();

    for (grep {/#include/} @lines) {
        if (m|crombie2/(\w+).h| && ! grep {/$1[^\.]/} @lines) {
            print "$infile doesn't need $_\n";
        }

        my ($included_file) = m/#include\s.([\w\/\.]+)/;

        my @tocheck = ();
        $eventual_included{$included_file}++;
        push @directly_included, $included_file;

        if ($included_file =~ /crombie2\//) {
            push @tocheck, $included_file;
        }

        while (scalar @tocheck) {
            my $nextfile = pop @tocheck;
            open (my $include_handle, '<', "include/$nextfile");
            for (<$include_handle>) {
                if (/#include .([\w\/]+\.h)/) {
                    $eventual_included{$1}++;
                    if (m|(crombie2/\w+\.h)|) {
                        push @tocheck, $1;
                    }
                }
            }
            close $include_handle;
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
