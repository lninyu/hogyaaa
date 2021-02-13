cd $(dirname $0)
git add ./
echo -n "> ";read ctext
if [ -n $ctext ];then
  stext = "$(date)"
fi
git commit -m "$ctext"
git push origin ugaaaaaa
