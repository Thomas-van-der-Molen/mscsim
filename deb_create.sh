#!/bin/bash

################################################################################

APP_NAME=mscsim
APP_VER=0.3

################################################################################

APP_DIR=${APP_NAME}_${APP_VER}_bionic_amd64

sudo rm -R $APP_DIR
sudo rm $APP_DIR.deb

mkdir $APP_DIR
mkdir $APP_DIR/DEBIAN
mkdir $APP_DIR/usr
mkdir $APP_DIR/usr/bin
mkdir $APP_DIR/usr/share
mkdir $APP_DIR/usr/share/applications
mkdir $APP_DIR/usr/share/icons
mkdir $APP_DIR/usr/share/icons/hicolor
mkdir $APP_DIR/usr/share/icons/hicolor/128x128
mkdir $APP_DIR/usr/share/icons/hicolor/128x128/apps

cp deb_mscsim_amd64.control $APP_DIR/DEBIAN/control
cp bin/mscsim $APP_DIR/usr/bin/
cp mscsim.desktop $APP_DIR/usr/share/applications/
cp mscsim.png $APP_DIR/usr/share/icons/hicolor/128x128/apps/

sudo chown root:root -R $APP_DIR
sudo chmod 0755 $APP_DIR/usr/bin/mscsim
sudo chmod 0755 $APP_DIR/usr/share/applications/mscsim.desktop
sudo chmod 0755 $APP_DIR/usr/share/icons/hicolor/128x128/apps/mscsim.png

dpkg -b $APP_DIR/

################################################################################

DATA_DIR=${APP_NAME}-data_${APP_VER}_bionic_all

sudo rm -R $DATA_DIR
sudo rm $DATA_DIR.deb

mkdir $DATA_DIR
mkdir $DATA_DIR/DEBIAN
mkdir $DATA_DIR/usr
mkdir $DATA_DIR/usr/share
mkdir $DATA_DIR/usr/share/mscsim

cp deb_mscsim-data_all.control $DATA_DIR/DEBIAN/control
cp -R data/ $DATA_DIR/usr/share/mscsim

sudo chown root:root -R $DATA_DIR/

dpkg -b $DATA_DIR/

################################################################################

read -p "Press any key to continue..." -n1 -s
