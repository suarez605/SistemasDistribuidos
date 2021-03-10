#!/bin/bash


if [[ "$1" == "-h" || "$1" == "--help" ]] 
then
    echo "USAGE -> script.sh arg1 ... argN :url1 ... :urlN"
    exit 0 
fi

objetos=()
direcciones=()
for var in $@
do
    if [[ $var == ":"* ]]
    then
        direcciones+=(${var:1})
    else
        objetos+=($var)
    fi
done

echo "Objetos recibidos:" + ${objetos[*]}
echo "------"
echo "URLs recibidas: " + ${direcciones[*]}
nObjetos=${#objetos[@]}
nDirecciones=${#direcciones[@]}


for obj in ${objetos[@]}
do
    #Primero calculamos el tamaño del objeto
    url="${direcciones[0]}/$obj"
    echo $url
    curl ${url} -I -s > headers

    size=$(cat headers | grep -i Content-Length | awk '{print $2}' 2>&1)

    echo "File Size = $size"
    
    # ahora debemos realizar un curl con todas las direcciones y a cada una solicitarle un trozo del objeto usando las cabeceras
    
    

done

