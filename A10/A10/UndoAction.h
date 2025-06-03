#pragma once
#include "Movie.h"
class Service;

class UndoAction {
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual ~UndoAction() = default;
};

class UndoAdd : public UndoAction {
    Service& service;
    Movie movie;
public:
    UndoAdd(Service& s, const Movie& m);
    void undo() override;
    void redo() override;
};

class UndoRemove : public UndoAction {
    Service& service;
    Movie movie;
public:
    UndoRemove(Service& s, const Movie& m);
    void undo() override;
    void redo() override;
};

class UndoUpdate : public UndoAction {
    Service& service;
    Movie oldMovie, newMovie;
public:
    UndoUpdate(Service& s, const Movie& oldM, const Movie& newM);
    void undo() override;
    void redo() override;
};
