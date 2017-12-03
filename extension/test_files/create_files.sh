list_of_test_files=(
  lorem
  ipsum
  dolor
  sit
  amet
)

rm -rf ./*.txt

for item in "${list_of_test_files[@]}"
do 
  echo "this is ${item}.txt" >> ${item}.txt
done 