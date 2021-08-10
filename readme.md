# GNU Web Scraping
Web scraping with C 
## Building
```
gcc -o scraping scraping.c
```
## Run
If you have GNU Wget
```
./scraping <link>
```
[if not](https://www.gnu.org/software/wget/), comment line
```
#define _ENABLE_WGET_ 
```
## Tag
For get specific tag, remove comment of this like
```
//#define HTML_TAG "<tag>"
```