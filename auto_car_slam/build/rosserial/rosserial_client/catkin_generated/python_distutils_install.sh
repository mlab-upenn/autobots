#!/bin/sh -x

if [ -n "$DESTDIR" ] ; then
    case $DESTDIR in
        /*) # ok
            ;;
        *)
            /bin/echo "DESTDIR argument must be absolute... "
            /bin/echo "otherwise python's distutils will bork things."
            exit 1
    esac
    DESTDIR_ARG="--root=$DESTDIR"
fi

cd "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_client"

# Note that PYTHONPATH is pulled from the environment to support installing
# into one location when some dependencies were installed in another
# location, #123.
/usr/bin/env \
    PYTHONPATH="/home/zhili/hector_slam_tutorial/auto_car_slam/install/lib/python2.7/dist-packages:/home/zhili/hector_slam_tutorial/auto_car_slam/build/lib/python2.7/dist-packages:$PYTHONPATH" \
    CATKIN_BINARY_DIR="/home/zhili/hector_slam_tutorial/auto_car_slam/build" \
    "/usr/bin/python" \
    "/home/zhili/hector_slam_tutorial/auto_car_slam/src/rosserial/rosserial_client/setup.py" \
    build --build-base "/home/zhili/hector_slam_tutorial/auto_car_slam/build/rosserial/rosserial_client" \
    install \
    $DESTDIR_ARG \
    --install-layout=deb --prefix="/home/zhili/hector_slam_tutorial/auto_car_slam/install" --install-scripts="/home/zhili/hector_slam_tutorial/auto_car_slam/install/bin"
