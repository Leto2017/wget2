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
-i --infile=<path> = path to the input txt- файлу со списком http-ссылок<br/>
-s --savedir=<path> = путь до папки, где сохранять html-страницы<br/>
-g --getimages = закачивать картинки с html страницы<br/>
-v --verbose = печатать в stdout подробно производимые операции, без этого флага печатать только ошибки<br/>
-h --help =  показать как использовать программу, выдать аргументы консоли<br/>
