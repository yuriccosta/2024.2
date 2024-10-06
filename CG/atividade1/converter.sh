for img in *.pnm; do
    convert "$img" "${img%.pnm}.jpg"
done
