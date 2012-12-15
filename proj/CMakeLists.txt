if(APPLE)
	set(SDL_LIBRARIES "-L/opt/local/lib -lSDLmain -lSDL -Wl,-framework,Cocoa") 
else()
	set(SDL_LIBRARIES "${SDLMAIN_LIBRARY} ${SDL_LIBRARY}") 
endif(APPLE)

set(S3D_LIBRARIES laux gp gutil geom color img lang poly prim csg gener view clip raster shade scene hier visib ray rad map plot anim)

set(S3D_LIBRARIES ${S3D_LIBRARIES} pbm)

add_subdirectory(ple) 
add_subdirectory(vw) 
add_subdirectory(rsurf) 
add_subdirectory(csg) 
add_subdirectory(ortho) 
add_subdirectory(anim) 
add_subdirectory(splot) 
add_subdirectory(zflat) 
add_subdirectory(rt) 
add_subdirectory(zsort) 
add_subdirectory(ray) 
add_subdirectory(rad) 
add_subdirectory(map) 
add_subdirectory(zmap) 
add_subdirectory(tk) 
add_subdirectory(rmap)


