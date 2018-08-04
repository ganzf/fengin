#!/usr/bin/env bash

# Before creating the module, it could be nice to check if there isn't a folder that exists with this name.
# Also it could be useful to add a script that downloads the latest version of the library

echo "Creating module $1"
# If the FenderTemplatesDirectory is missing, we download it from the repository.

# We copy the templates directory
cp -r ./TemplateSystem $1

# Rename the files
mv $1/TEMPLATE.cpp $1/$1.cpp
mv $1/TEMPLATE.hpp $1/$1.hpp
mv $1/TEMPLATE.md $1/$1.md

# Replace the keyword TEMPLATE_MODULE_NAME to the name chosen by the user
sed -i "s/TEMPLATE_MODULE_NAME/$1/g" $1/CMakeLists.txt
sed -i "s/TEMPLATE_MODULE_NAME/$1/g" $1/$1.cpp
sed -i "s/TEMPLATE_MODULE_NAME/$1/g" $1/$1.hpp
sed -i "s/TEMPLATE_MODULE_NAME/$1/g" $1/$1.md
DATENOW=`date +%Y-%m-%d`
sed -i "s/TEMPLATE_MODULE_CREATION_DATE/$DATENOW/g" $1/$1.cpp
sed -i "s/TEMPLATE_MODULE_CREATION_DATE/$DATENOW/g" $1/$1.hpp
sed -i "s/TEMPLATE_MODULE_CREATION_DATE/$DATENOW/g" $1/$1.md
USERNAME=$USER
sed -i "s/TEMPLATE_MODULE_CREATOR/$USERNAME/g" $1/$1.cpp
sed -i "s/TEMPLATE_MODULE_CREATOR/$USERNAME/g" $1/$1.hpp
sed -i "s/TEMPLATE_MODULE_CREATOR/$USERNAME/g" $1/$1.md

# Prompt the user for a short description of the module he creates.
echo "Describe your module in a few words. It will be written in the $1.md file: "
read -p "" desc
sed -i "s/TEMPLATE_MODULE_DESCRIPTION/${desc}/g" $1/$1.md

echo 'Done'

