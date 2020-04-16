#install.packages('tuneR', dep=TRUE)
#install.packages('seewave', dep=TRUE)
#install.packages('soundgen', dep=TRUE)

library(tuneR)
library(seewave)
#library(soundgen)
library(audio)

# establecer el path concreto en cada caso a la carpeta de trabajo
setwd("/home/divadhp/Universidad/PDIH/S6/S6-varios-sonidos/")
# la siguiente l??nea, s??lo para macOS
setWavPlayer('/usr/bin/mpv')

# cargar archivos de sonido (wav/mp3):
perro <- readWave('perro.wav')
perro
gato  <- readMP3('gato.mp3')
gato


# mostrar la onda del sonido:
plot( extractWave(gato, from = 1, to = 393984) )
plot( extractWave(perro, from = 1, to = 159732) )

# Mostar los heardes
perro
gato

# Se pueden leer solamente los headers de un archivo usando:
# headers <- readWave('perro.wav', header = TRUE)
# headers

# Unir ambos sonidos
sonido <- pastew(perro, gato, output = "Wave")
sonido
plot( extractWave(sonido, from = 1, to = 553716) )
f <- sonido@samp.rate    #44100

a <- bwfilter(sonido,f=f, from=0, to=3000, output = "Wave", bandpass = TRUE)
a
plot( extractWave(a, from = 1, to = 553716) )
listen(a, f=f)
writeWave(a, file.path("sonido-filtrado.wav"))

# Grabar sonido de 2 segundos

s <- record(16000, 8000, 1)
wait(s)
x <- s$data
close(s); rm(s)

listen(x, f=8000)
