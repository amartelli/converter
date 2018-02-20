# converter
==============

For conversion from Delphes to files used for training.
After conversion (please mind naming scheme w.r.t. MC/data, qcd/ttbar), merge the output files in the following way:

create a text file for each listing: ttbar data, ttbar MC, qcd data, qcd MC (4 files in total).

run mergeSamples.py <number of jets per file, use around 100000> <output dir, e.g. merged> <all input text files>

Then run the conversion to DeepJet from the 'samples.txt' output file produced by it.
