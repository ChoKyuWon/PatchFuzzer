git clone $1 target
cd target
git format-patch -100
cd ../
mv target/*.patch ./
python3 parse.py && rm -rf target *.paatch