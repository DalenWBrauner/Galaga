/*
This file includes anything ALL files need without redundant #include statements.

Current shape of #include web:

Galaga.h <- World.h <- Aircraft.h <- Entity.h <- SceneNode.h <- Inclusion.h

(With each .cpp including its .h namesake.)
*/
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>