### Nei commenti che seguono vedete dei suggerimenti sull'algoritmo da
### seguire per produrre l'output corretto.
###

MATRICOLE=""
# I voti della seconda prova li devo mettere tutti nello standard output
while read matricola voto; do
    echo "${matricola} ${voto}"
    MATRICOLE="${MATRICOLE} ${matricola}"
done < esame2.txt 

# Poi devo mettere nello standard output i voti della prima prova
# ottenuti dagli studenti che non hanno un voto nella seconda prova
while read matricola voto; do
    found=1
    for check in $MATRICOLE; do
        if [[ $check -eq $matricola ]]; then
            found=0
        fi
    done
    if (( $found == 1 )); then
        echo "${matricola} ${voto}"
    fi
done < esame1.txt 


