##
## CMakeLists.txt for ParticleSystem in /ParticleSystem/Shape/BoxShape
## 
## Made by Louis Martin-Pierrat
## Login   <mart_p@epitech.net>
## 
## Started on  Fri Oct 17 17:04:21 2014 Louis Martin-Pierrat
## Last update Fri Oct 17 17:04:30 2014 Louis Martin-Pierrat
##

## INCLUDE DIRECTORY

GET_PROPERTY(IDIR GLOBAL PROPERTY INCLUDEDIR)
SET(IDIR
	${IDIR}
	${CMAKE_CURRENT_SOURCE_DIR}/
	)
SET_PROPERTY(GLOBAL PROPERTY INCLUDEDIR ${IDIR})

## END INCLUDE DIRECTORY



## SET SOURCES FILES

GET_PROPERTY(SRCS GLOBAL PROPERTY SOURCES)
SET(SRCS
	${SRCS}
	${CMAKE_CURRENT_SOURCE_DIR}/BoxShape.cpp
	)
SET_PROPERTY(GLOBAL PROPERTY SOURCES ${SRCS})

## END
