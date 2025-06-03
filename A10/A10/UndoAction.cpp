#include "UndoAction.h"
#include "Service.h"

UndoAdd::UndoAdd(Service& s, const Movie& m) : service(s), movie(m) {}

void UndoAdd::undo() { 
    service.removeMovieDirect(movie.getTitle()); 
}

void UndoAdd::redo() {
    service.addMovieDirect(movie); 
}

UndoRemove::UndoRemove(Service& s, const Movie& m) : service(s), movie(m) {}

void UndoRemove::undo() { 
    service.addMovieDirect(movie); 
}

void UndoRemove::redo() { 
    service.removeMovieDirect(movie.getTitle()); 
}

UndoUpdate::UndoUpdate(Service& s, const Movie& oldM, const Movie& newM)
    : service(s), oldMovie(oldM), newMovie(newM) {
}

void UndoUpdate::undo() {
    service.updateMovieDirect(oldMovie);
}
void UndoUpdate::redo() {
    service.updateMovieDirect(newMovie);
}
