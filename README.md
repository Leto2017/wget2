# wget2
A project that retrieves content (html and images) from web pages.

Command line arguments:<br/>
Usage: <option(s)> SOURCES<br/>
Option:<br/>
-u --url=<string> = the http-address to download web-page<br/>
-r --recursive       = load pages by links found in the download pages<br/>
-l --level=<uint> = глубина рекурсивного скачивания сайта по ссылкам на скачанных страницах<br/>
-t --tries=<uint> = число попыток скачать страницу до выдачи ошибки<br/>
-n --no-parent    = загружать страницы не выше по иерархии заданной<br/>
-i --infile=<path> = путь к входному txt файлу со списком http-ссылок<br/>
-s --savedir=<path> = путь до папки, где сохранять html-страницы<br/>
-g --getimages = закачивать картинки с html страницы<br/>
-v --verbose = печатать в stdout подробно производимые операции, без этого флага печатать только ошибки<br/>
-h --help =  показать как использовать программу, выдать аргументы консоли<br/>
