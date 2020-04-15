if docker ps -a |grep -q compiler ; then
    echo "Stopping container..."
    docker stop compiler
    echo "Container stopped"
else
    echo "Container already stopped"
fi