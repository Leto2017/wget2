# wget2
A project that retrieves content (html and images) from web pages.

Command line arguments:<br/>
Usage: <option(s)> SOURCES<br/>
Option:<br/>
-u --url=<string> = the http-address to download web-page<br/>
-r --recursive       = load pages by links found in the download pages<br/>
-l --level=<uint> = depth of recursive webpages download by links from downloaded pages<br/>
-t --tries=<uint> = the number of attempts to download the page before issuing an error<br/>
-n --no-parent    = load pages no higher than a given hierarchy<br/>
-i --infile=<path> = path to the input txt-file with the list of http-links<br/>
-s --savedir=<path> = path to the directory where html-page is stored<br/>
-g --getimages = download images from html-page<br/>
-v --verbose = print to stdout detailed operations, without this flag, print only errors<br/>
-h --help =  show how to use the program, give console arguments<br/>
