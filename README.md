# wget2
A project that retrieves content (html and images) from web pages.

Command line arguments:
Usage: <option(s)> SOURCES
Options:
-u --url=<string> = the http-address to download web-page
-r --recursive       = load pages by links found in the download pages
-l --level=<uint> = глубина рекурсивного скачивания сайта по ссылкам на скачанных страницах
-t --tries=<uint> = число попыток скачать страницу до выдачи ошибки
-n --no-parent    = загружать страницы не выше по иерархии заданной
-i --infile=<path> = путь к входному txt файлу со списком http-ссылок
-s --savedir=<path> = путь до папки, где сохранять html-страницы
-g --getimages = закачивать картинки с html страницы
-v --verbose = печатать в stdout подробно производимые операции, без этого флага печатать только ошибки
-h --help =  показать как использовать программу, выдать аргументы консоли
