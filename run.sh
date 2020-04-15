if docker ps -a |grep -q compiler ; then
    echo "Container is already running"
else
    echo "Container not started"
    echo "Starting container..."
    docker run --rm --name compiler -v "$(pwd)":/compiler -t -d -w /compiler eguerin/antlr4cpp
    echo "Container started"
fi

echo "Entering container using bash"
docker exec -it compiler bash