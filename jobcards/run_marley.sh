#!/bin/bash

# Generate Marley events
cd ../marley/build
marley ../examples/config/annotated.js
marsum MARLEY.flat.root events.ascii
mv MARLEY.flat.root ../../jobcards/samples/

# Remove unnecessary files
rm marley_root_dict_rdict.pcm
rm events.ascii
