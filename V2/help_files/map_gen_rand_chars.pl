#!/usr/bin/perl

use warnings;
use strict;

die "program x y density" unless (scalar(@ARGV) == 3);

my ($x, $y, $density) = @ARGV;

my $empty;
my $wall;
my $fill;

my %unique_chars;
while (keys %unique_chars < 3) {
	my $random_char = chr(int(rand(95)) + 32);
	$unique_chars{$random_char} = 1;
}

my @chars = keys %unique_chars;
$empty = $chars[0];
$wall = $chars[1];
$fill = $chars[2];

print "$y$empty$wall$fill\n";

for (my $i = 0; $i < $y; $i++) {
	for (my $j = 0; $j < $x; $j++) {
		if (int(rand($y) * 2) < $density) {
			print "$wall";
		}
		else {
			print "$empty";
		}
	}
	print "\n";
}