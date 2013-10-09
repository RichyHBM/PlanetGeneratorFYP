-- A solution contains projects, and defines the available configurations
solution "PlanetGeneratorFYP"
   configurations { "Debug", "Release" }
   location "build"

   dofile "./standalone.lua"
   dofile "./test.lua"
   dofile "./server.lua"
   dofile "./client.lua"
