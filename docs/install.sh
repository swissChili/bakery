# Bake installer

echo "Cloning bake into temporary directory for compilation"
cd ~
rm -rf ~/.bake/temp
mkdir -p .bake/temp
green="\033[38;5;43m"
red="\033[38;5;203m"
reset="\033[0m"

worked() {
	if [ "$?" -eq "0" ]; then
		echo -e "$green✓ Done$reset"
	else
		echo -e "$red🗴 Failed$reset"
	fi
}

cd .bake/temp
git clone https://github.com/swissChili/bakery.git
cd bakery/src
echo "Compiling bake with g++"
g++ -o bake bake.cpp -std=c++17
worked
g++ -o baked daemon.cpp -std=c++17
echo "Compiling bake daemon with g++"
worked

echo "Installing bake, root access required"

sudo mv bake /usr/bin/bake
worked
sudo mv baked /usr/bin/baked
worked
sudo cp baketools/baketools.sh /usr/bin/baketools.sh
worked

echo "Testing if docker is installed"
echo "If this fails, please install docker-ce and continue"
docker >> /dev/null
worked

echo "Cleaning up"
cd ~
rm -rf .bake
