# EquitableFireHydrantPlacement
Repository for my source code for the 2023 D2P through Auraria Library

# Necessary Files
First, you need to install ampl into this directory. Due to potential licensing issues, I did not include it here,
however you can download the community edition from https://ampl.com/ce/

Depending on the file name, you may need to also change the file path inside runClustering.sh, runLocation.sh, and their respective command files.

You will also need to generate the "houses.json" file. It cannot be included in this repository due to the large file size, and limitations with github

To generate it you will need to 
1. go to overpass-turbo.eu
2. Do either: 
    * Inside the editor, paste:
```
/*
This has been generated by the overpass-turbo wizard.
The original search was:
“ building in Denver”
*/
[out:json][timeout:25];
// fetch area “Denver” to search in
{{geocodeArea:Denver}}->.searchArea;
// gather results
(
  // query part for: “building”
  way["building"](area.searchArea);
  relation["building"](area.searchArea);
);
// print results
out body;
>;
out skel qt;
```
This will be a very large file.

* Paste: overpass-api.de/api/interpreter?data=%2F*%0AThis%20has%20been%20generated%20by%20the%20overpass-turbo%20wizard.%0AThe%20original%20search%20was%3A%0A%E2%80%9C%20building%20in%20Denver%E2%80%9D%0A*%2F%0A%5Bout%3Ajson%5D%5Btimeout%3A25%5D%3B%0A%2F%2F%20fetch%20area%20%E2%80%9CDenver%E2%80%9D%20to%20search%20in%0Aarea%28id%3A3601411339%29-%3E.searchArea%3B%0A%2F%2F%20gather%20results%0A%28%0A%20%20%2F%2F%20query%20part%20for%3A%20%E2%80%9Cbuilding%E2%80%9D%0A%20%20way%5B%22building%22%5D%28area.searchArea%29%3B%0A%20%20relation%5B%22building%22%5D%28area.searchArea%29%3B%0A%29%3B%0A%2F%2F%20print%20results%0Aout%20body%3B%0A%3E%3B%0Aout%20skel%20qt%3B

into a web browser.

The former will allow you to investigate the data yourself, while the latter will just download the file and is 
less likely to cause issues due to the amount of data.
# Compilation Instructions
1. ```make```
2. Open "parsing.ipynb" inside jupyter notebooks (Or run the parsing.py file. Some of the figures won't display this way, but it will save all the ones saved)
3. Enjoy!

# Potential Things to Investigate
* Change the penalty inside Location.mod
* Change max number of houses per hydrant in Location.mod
    * This is VERY memory intensive, and can make the program take a LONG time to terminate depending on your hardware
* Look at different regions by determing latitude and longitude
