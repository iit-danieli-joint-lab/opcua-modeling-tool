## Compile on Ubuntu 18.04 

### Install dependencies 
~~~
sudo apt-get install libxerces-dev libwxgtk3.0-dev
wget https://www.codesynthesis.com/download/xsd/4.0/linux-gnu/x86_64/xsd_4.0.0-1_amd64.deb
sudo dpkg -i xsd_4.0.0-1_amd64.deb
~~~

### Compile 
Run:
~~~
make
~~~

### Execute
Run: 
~~~
./eXcelerator
~~~
