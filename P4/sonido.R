library(tuneR)
library(seewave)
#library(soundgen)
library(audio)


setwd("/home/divadhp/Universidad/PDIH/P4/sonidos")
setWavPlayer('/usr/bin/mpv')

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
writeWave(a, file.path("mezla.wav"))


hola <- readWave('hola.wav')
listen(hola, hola@samp.rate)
s <- echo(hola, hola@samp.rate, amp=c(1, 0.4, 0.2), delay=c(1, 2, 3), output = "Wave")
s <- revw(s, f=s@samp.rate, output = "Wave")
writeWave(s, file.path("alreves.wav"))
listen(s, s@samp.rate)
