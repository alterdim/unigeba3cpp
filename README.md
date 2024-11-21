[![SFML logo](https://www.sfml-dev.org/images/logo.png)](https://www.sfml-dev.org)
## Building

1. Install CMAKE with your favorite package manager.
2. Make sure you have the following packages installed:
    ```
    sudo apt update
    sudo apt install \
        libxrandr-dev \
        libxcursor-dev \
        libudev-dev \
        libfreetype-dev \
        libopenal-dev \
        libflac-dev \
        libvorbis-dev \
        libgl1-mesa-dev \
        libegl1-mesa-dev
    ```
3. Complie with :
    ```
    cmake -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build --config Release
    ```
4. Enjoy!

## Playing
Click the coin to increase your score. Avoid the slimes !

This game uses 
https://opengameart.org/ assets.

