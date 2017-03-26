php tinycdb extension
=====================


Development guide
-----------------

### install dev php5.6.30

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

### build

```
 ${HOME}/php-ext/bin/phpize
 ./configure --help | grep tinycdb
 ./configure --enable-tinycdb --with-php-config=${HOME}/php-ext/bin/php-config
 make
```

### test 

```
# create cdb command
 cd vendor/tinycdb; make; cd -

# create sample.cdb
 ./vendor/tinycdb/cdb -c -m sample.cdb sample.tsv
 ./vendor/tinycdb/cdb -c -m sample2.cdb sample2.tsv
 cp sample.cdb sample2.cdb /dev/shm/

# run test.php
 ${HOME}/php-ext/bin/php -d extension=modules/tinycdb.so -f test.php
```
