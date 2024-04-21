# Environmental Setup for the Crazyflie Swarm-Blockchain Project

Based from Dr. Volker Strobel: https://iridia.ulb.ac.be/~vstrobel/articles/StrPacDor2023scirobotics.pdf

## Installation of ARGoS: 
1.	Install dependencies:
```shell
$ sudo apt-get install git build-essential cmake g++ libfreeimage-dev \
libfreeimageplus-dev qt5-default freeglut3-dev libxi-dev libxmu-dev \
liblua5.3-dev lua5.3 doxygen graphviz graphviz-dev asciidoc
```
2.	Obtain the source code of ARGOS:
```shell
$ git clone https://github.com/ilpincy/argos3.git
```
3.	Build and install ARGoS system-wide
```shell
$ git clone https://github.com/ilpincy/argos3.git $
$ cd argos3/
$ mkdir build
$ cd build
$ cmake ../src
$ make -j4
$ make doc
$ sudo make install
$ sudo ldconfig
```
4.	Verify that the installation was successful
```shell
$ argos3 --version
ARGOS_VERSION=3.0.0-beta59
ARGOS_INSTALL_PREFIX=/usr/local
ARGOS_USE_DOUBLE=ON
ARGOS_WITH_LUA=ON
ARGOS_BUILD_FLAGS= -Wall -g -ggdb3
```

Installation of the ARGoS E-puck Plugin: 
1.	Obtain source code:
```shell
$ git clone https://github.com/demiurge-project/argos3-epuck.git
```
2.	Build and install the ARGoS E-puck plugin
```shell
$ cd argos3-epuck/
$ mkdir build
$ cd build
$ cmake ../src
$ make
$ sudo make install
$ sudo ldconfig
```

## Installation of Docker: 
Full installation documentations: https://docs.docker.com/engine/install/ubuntu/
1.	Set up Docker's apt repository. Add Docker's official GPG key:
```shell
$ sudo apt-get update
$ sudo apt-get install ca-certificates curl
$ sudo install -m 0755 -d /etc/apt/keyrings
$ sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
$ sudo chmod a+r /etc/apt/keyrings/docker.asc
```
2.	Add the repository to Apt sources:
```shell
$ echo \
  "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
$ sudo apt-get update
```

3.	Install the Docker packages.
```shell
$ sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```
4.	Verify that the Docker Engine installation is successful by running the hello-world image.
```shell
$ sudo docker run hello-world
```

### How to control the Docker Engine as a non-root user:
1.	By default, the execution of Docker commands requires root user privileges. To facilitatethe execution of Docker commands, it is possible to run Docker as a non-root user (that is, also without using sudo ) as follows:
```shell
$ sudo groupadd docker
$ sudo usermod -aG docker $USER
$ newgrp docker
```
2.	By Additionally, restarting the Docker engine via systemctl requires sudo privileges. To con-trol Docker as a normal user, add an entry in the sudoers file (replace <user> with your username).
```shell
$ sudo visudo -f /etc/sudoers.d/docker
<user> ALL= NOPASSWD: /bin/systemctl restart docker.service
<user> ALL= NOPASSWD: /bin/systemctl start docker.service
<user> ALL= NOPASSWD: /bin/systemctl stop docker.service
```
For example, user is herzon:
```shell
herzon ALL= NOPASSWD: /bin/systemctl restart docker.service
herzon ALL= NOPASSWD: /bin/systemctl start docker.service
herzon ALL= NOPASSWD: /bin/systemctl stop docker.service
```

## Installation of the simulation framework (Volker Strobel)
1.	First, the dependencies have to be installed
```shell
$ sudo apt-get install g++ cmake git libboost-python-dev
```shell
2.	Then, the source code of our simulation framework must be downloaded.
```shell
$ git clone --recurse-submodules \
https://github.com/iridia-ulb/blockchain-simulations.git
```
3.	Alternatively download or clone the argos-python manually: https://github.com/KenN7/argos-python/tree/993f2d29cb0a77fc457097dc9833ddd38967b988
```shell
$ git clone https://github.com/KenN7/argos-python
```

4.	First, the dependencies have to be installed
```shell
$ cd blockchain-simulations/argos-python
$ git fetch
$ git checkout temp
$ mkdir build
$ cd build
$ cmake ..
$ make
```

5.	 First, the dependencies have to be installed Then the Docker image must be created. The image contains the Ethereum software and other scripts that simplify the interaction with Ethereum. Furthermore, the Docker swarm must be initialized. A Docker swarm provides the ability to launch many Docker containers in parallel and allows for assigning limits to each container, such as how much CPU and RAM it can consume.
```shell
$ cd argos-blockchain/geth/
$ docker build -t mygeth .
$ docker swarm init
```

6.	Our smart contracts are written in the Solidity programming language. For this reason, solc, a compiler for Solidity, must be installed.
```shell
$ sudo add-apt-repository ppa:ethereum/ethereum
$ sudo apt-get update
$ sudo apt-get install solc
```

7.	The Python controllers require additional packages.
```shell
$ sudo apt install python3-pip
$ pip3 install rpyc psutil
```

8.	Optional: Experiment 1b uses a dynamic floor layout. The following steps are required to be able to create new floor layouts at the start of each experiment.
```shell
$ sudo apt install python3-pip
$ pip3 install numpy
$ pip3 install matplotlib
$ sudo apt install imagemagick
```

## Setup of variables
In the following steps, we set variables so that the different modules are connected with each
other.
1.	First, the blockchain module needs to be linked to the parent folder that contains the different modules. For this purpose, the variable MAINFOLDER in the file global_config_blockchain.sh needs to be edited to point to the parent folder.
```shell
$ vim argos-blockchain/local_scripts/global_config_blockchain.sh
MAINFOLDER="$HOME/blockchain-simulations"
```

2.	Subsequently, the experiment folder must also know where the parent folder is located. Edit the variable MAINFOLDER in the file experimentconfig.sh :
```shell
$ vim blockchain-simulations/FloorEstimation/experimentconfig.sh
export MAINFOLDER="$HOME/blockchain-simulations"
```
 
## Additional Dependencies
Install the additional dependencies for the ARGoS-Blockchain project

1.	RPyC (https://rpyc.readthedocs.io/)
```shell
$ pip3 install rpyc
```

2.	Aenum (https://pypi.org/project/aenum//)
```shell
$ pip3 install aenum
```

3.	Hexbytes (https://pypi.org/project/hexbytes/)
```shell
$ pip3 install hexbytes
```

4.	Web.py (https://web3py.readthedocs.io/en/stable/)
```shell
$ pip3 install web3 
```

5.	graphviz (https://pypi.org/project/graphviz/
```shell
$ pip3 install graphviz
```

6.	seaborn (https://seaborn.pydata.org/installing.html)
```shell
$ pip3 install seaborn
```

7.	pydotplus (https://pypi.org/project/pydotplus/)
```shell
$ pip3 install pydotplus
```

8.	networkX (https://networkx.org/documentation/stable/install.html)
```shell
$ pip3 install networkx[default]
```

9.	seaborn (https://seaborn.pydata.org/installing.html)
```shell
$ pip3 install seaborn 
```

## Installation of the ARGoS-Crazyflie Base Model Plugin
1.	Obtain source code:
```shell
$ git clone https://github.com/marckbarrion/argos-crazyflie_prereq
```
2.	Build and install the ARGoS Crazyflie plugin
```shell
$ cd argos-crazyflie_prereq/
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ../src
$ make
$ sudo make install
```

3.	If ARGoS does not find the new robot, try:
```shell
$ cmake -DCMAKE_BUILD_TYPE=Release ../src -DCMAKE_INSTALL_PREFIX=/usr/local 
```

Or alternatively,
```shell
$ cmake -DCMAKE_BUILD_TYPE=Release ../src -DCMAKE_INSTALL_PREFIX=/usr
```

For debug builds:
```shell
$ cmake -DCMAKE_BUILD_TYPE=Debug
```

## Installation of the ARGoS-Crazyflie Python Wrapper
1.	Obtain source code:
```shell
$ git clone https://github.com/marckbarrion/argos-crazyflie_python-wrapper
```
2.	Go to the installation root directory
```shell
$ cd argos-crazyflie_python-wrapper
```

3.	Build and compile using CMake
```shell
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release ..
$ make
```

## Installation of Git Linux
Git Linux: https://github.com/git-guides/install-git
1.	It's a good idea to make sure you're running the latest version. To do so, Navigate to your command prompt shell and run the following command to make sure everything is up-to-date:
```shell
$ sudo apt-get update 
```

2.	To install git, run the following command:
```shell
$ sudo apt-get install git-all
```

3.	Once the command output has completed, you can verify the installation by typing: 
```shell
$ git-all git version
```

## Installation of GitHub Desktop

GitHub Desktop: https://github.com/shiftkey/desktop

1.	There are two APT package feeds available, both hosted in the US. You only need to add one or the other here, as both of these are generated based on the releases from this repository.

@shiftkey package feed
```shell
$ wget -qO - https://apt.packages.shiftkey.dev/gpg.key | gpg --dearmor | sudo tee /usr/share/keyrings/shiftkey-packages.gpg > /dev/null
$ sudo sh -c 'echo "deb [arch=amd64 signed-by=/usr/share/keyrings/shiftkey-packages.gpg] https://apt.packages.shiftkey.dev/ubuntu/ any main" > /etc/apt/sources.list.d/shiftkey-packages.list'
```

@mwt package feed
```shell
$ wget -qO - https://mirror.mwt.me/shiftkey-desktop/gpgkey | gpg --dearmor | sudo tee /usr/share/keyrings/mwt-desktop.gpg > /dev/null
$ sudo sh -c 'echo "deb [arch=amd64 signed-by=/usr/share/keyrings/mwt-desktop.gpg] https://mirror.mwt.me/shiftkey-desktop/deb/ any main" > /etc/apt/sources.list.d/mwt-desktop.list'
```

2.	Once you have a feed configured, run this command to install the application:
```shell
$ sudo apt update && sudo apt install github-desktop
```

