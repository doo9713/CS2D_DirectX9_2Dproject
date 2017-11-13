#pragma once

#define CF(classfunctor) [this]() { classfunctor(); }
#define BCF(boolclassfunctor) [this]() -> bool { return boolclassfunctor(); }