php tinycdb extension
=====================


Development guide
-----------------

# install dev php5.6.30

```
 mkdir ${HOME}/work ${HOME}/php-ext
 cd ${HOME}/work
 git clone https://github.com/php/php-src.git
 cd php-src/
 git checkout php-5.6.30
 ./buildconf --force
 ./configure --prefix=${HOME}/php-ext --enable-debug
 make -j 30
 make install
```

# build

```
 ${HOME}/php-ext/bin/phpize
 ./configure --help | grep php_tinycdb
 ./configure --enable-php_tinycdb --enable-debug --with-php-config=${HOME}/php-ext/bin/php-config
 make
```

# test 

```
# create cdb command
 cd tinycdb; make; cd -

# create sample.cdb
 ./tinycdb/cdb -c -m sample.cdb sample.tsv
 cp sample.cdb /dev/shm/sample.cdb

# run test.php
 ${HOME}/php-ext/bin/php -d extension=modules/php_tinycdb.so -f test.php
```
