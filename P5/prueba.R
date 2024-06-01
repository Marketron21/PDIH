library(tuneR)
library(seewave)
library(audio)
nombre <- readWave('Nombre.wav')
apellido <- readWave('Apellido.wav')
nombre
apellido
listen(nombre)
listen(apellido)

plot(extractWave(nombre, from=1, to=86400))
plot(extractWave(apellido, from=1, to=110880))

str(nombre)
str(apellido)

nom_ape <- pastew(apellido, nombre, output = "Wave")
nom_ape
listen(nom_ape)

plot(extractWave(nom_ape, from=1, to=197280))

filtrado <- bwfilter(nom_ape, f=48000, from=10000, to=20000,
                     bandpass=TRUE, listen = FALSE, output = "Wave")
filtrado
listen(filtrado, f=48000)
plot(extractWave(filtrado, from=1, to=197280))

filtrado <- normalize(filtrado, unit="16", center = TRUE, level = 1)

writeWave(filtrado, file.path("mezcla.wav") )
str(filtrado)

burger <- readWave('burger.wav')
burgerECHO <- echo(burger,f=48000,amp=c(0.8,0.4,0.2),delay=c(0.6,1.2,1.8),
                   output="Wave")
listen(burgerECHO)
alreves <- revw(burgerECHO, output="Wave")
listen(alreves)
alreves <- normalize(alreves, unit="16", center = TRUE, level = 1)
writeWave(alreves, file.path("alreves.wav") )
