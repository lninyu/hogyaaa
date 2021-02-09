cd $(dirname $0)/../
git add ./
echo $(git commit -m "$(date)"|head -n 2|tail -n 1) | tee -a hogyaaa.txt
git push origin ugaaaaaa
