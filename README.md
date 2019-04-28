# wget2
This project retrieves content (html and images) from web pages.

## Getting started

### Run wget from solution

To run a solution follow steps listed below:

1. Download all files.

2. Open solution in a folder and build solution.

3. Open solution in a folder and run solution.

4. Install nc program. Open command line and use following command line arguments:

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
  
 ### Additional information

### libcurl

This projuct uses curl library. So if you don't have one, install it by following istructions:

1. Download curl from https://curl.haxx.se/download.html

2. Extract downloaded package to a folder of your choice (e.g. C:\curl\)

3. Open Developer Command Prompt for VS 2017 (see Windows Start menu or %PROGRAMDATA%\Microsoft\Windows\Start Menu\Programs\Visual Studio 2017\Visual Studio Tools\) and cd to C:\curl\

4. Run nmake /f Makefile.vc mode=static. This will build curl as a static library into C:\curl\builds\libcurl-vc-x86-release-static-ipv6-sspi-winssl\

5. Create a new project in Visual Studio (e.g. a Windows Console Application) or open already existing project.

6. In Project Properties -> VC++ Directories -> Include Directories add C:\curl\builds\libcurl-vc-x86-release-static-ipv6-sspi-winssl\include\

7. In Project Properties -> VC++ Directories -> Library Directories add C:\curl\builds\libcurl-vc-x86-release-static-ipv6-sspi-winssl\lib\

8. In Project Properties -> Linker -> Input -> Additional Dependencies add libcurl_a.lib, Ws2_32.lib, Crypt32.lib, Wldap32.lib and Normaliz.lib
 
NOTE that youe pather to curl library could differ from mentioned, so use your paths.
  
###getopt.h

This project also uses getopt library. 

You can get one here: https://github.com/skandhurkat/Getopt-for-Visual-Studio

