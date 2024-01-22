#include <naivecgl/Geometry/HalfEdgeMesh.h>

#include <tuple>

Naive_NAMESPACE_BEGIN(geometry);

/* HalfEdgeMesh::Vertex */

HalfEdgeMesh::Vertex::Vertex() : myCoord(), myEdge(nullptr), myId(-1) {}

HalfEdgeMesh::Vertex::Vertex(const Naive_Point3d &theCoord)
    : myCoord(theCoord), myEdge(nullptr), myId(-1) {}

HalfEdgeMesh::Vertex::Vertex(Naive_Real theX, Naive_Real theY, Naive_Real theZ)
    : myCoord(theX, theY, theZ), myEdge(nullptr), myId(-1) {}

HalfEdgeMesh::Vertex::Vertex(Vertex &&theOther) noexcept {
  myCoord = std::move(theOther.myCoord);
  myEdge = theOther.myEdge;
  theOther.myEdge = nullptr;
  myId = theOther.myId;
}

HalfEdgeMesh::Vertex &
HalfEdgeMesh::Vertex::operator=(Vertex &&theOther) noexcept {
  myCoord = std::move(theOther.myCoord);
  myEdge = theOther.myEdge;
  theOther.myEdge = nullptr;
  myId = theOther.myId;

  return *this;
}

HalfEdgeMesh::Vertex::~Vertex() {}

/* HalfEdgeMesh::HalfEdgeId */

HalfEdgeMesh::HalfEdgeId::HalfEdgeId() : myA(-1), myB(-1) {}

HalfEdgeMesh::HalfEdgeId::HalfEdgeId(const Naive_Integer theA,
                                     const Naive_Integer theB)
    : myA(theA), myB(theB) {}

Naive_Bool
HalfEdgeMesh::HalfEdgeId::operator!=(const HalfEdgeId &theOther) const {
  return myA != theOther.myA || myB != theOther.myB;
}

Naive_Bool
HalfEdgeMesh::HalfEdgeId::operator==(const HalfEdgeId &theOther) const {
  return myA == theOther.myA && myB == theOther.myB;
}

Naive_Bool HalfEdgeMesh::HalfEdgeId::IsValid() const {
  return myA >= 0 && myB >= 0;
}

Naive_Bool
HalfEdgeMesh::HalfEdgeId::operator<(const HalfEdgeId &theOther) const {
  if (myA < theOther.myA) {
    return true;
  } else if (myA == theOther.myA) {
    return myB < theOther.myB;
  } else {
    return false;
  }
}

Naive_Bool
HalfEdgeMesh::HalfEdgeId::operator>(const HalfEdgeId &theOther) const {
  if (myA > theOther.myA) {
    return true;
  } else if (myA == theOther.myA) {
    return myB > theOther.myB;
  } else {
    return false;
  }
}

Naive_Bool
HalfEdgeMesh::HalfEdgeId::operator<=(const HalfEdgeId &theOther) const {
  if (myA < theOther.myA) {
    return true;
  } else if (myA == theOther.myA) {
    return myB <= theOther.myB;
  } else {
    return false;
  }
}

Naive_Bool
HalfEdgeMesh::HalfEdgeId::operator>=(const HalfEdgeId &theOther) const {
  if (myA > theOther.myA) {
    return true;
  } else if (myA == theOther.myA) {
    return myB >= theOther.myB;
  } else {
    return false;
  }
}

/* HalfEdgeMesh::HalfEdge */

HalfEdgeMesh::HalfEdge::HalfEdge()
    : myOrigin(nullptr), myTwin(nullptr), myFace(nullptr), myNext(nullptr),
      myId() {}

HalfEdgeMesh::HalfEdge::HalfEdge(Vertex *theOrigin, Vertex *theNext)
    : myOrigin(theOrigin), myTwin(nullptr), myFace(nullptr), myNext(nullptr),
      myId(theOrigin->Id(), theNext->Id()) {}

HalfEdgeMesh::HalfEdge::HalfEdge(HalfEdge &&theOther) noexcept {
  myOrigin = theOther.myOrigin;
  myTwin = theOther.myTwin;
  myFace = theOther.myFace;
  myNext = theOther.myNext;
  theOther.myOrigin = nullptr;
  theOther.myTwin = nullptr;
  theOther.myFace = nullptr;
  theOther.myNext = nullptr;
  myId = theOther.myId;
}

HalfEdgeMesh::HalfEdge &
HalfEdgeMesh::HalfEdge::operator=(HalfEdge &&theOther) noexcept {
  myOrigin = theOther.myOrigin;
  myTwin = theOther.myTwin;
  myFace = theOther.myFace;
  myNext = theOther.myNext;
  theOther.myOrigin = nullptr;
  theOther.myTwin = nullptr;
  theOther.myFace = nullptr;
  theOther.myNext = nullptr;
  myId = std::move(theOther.myId);

  return *this;
}

HalfEdgeMesh::HalfEdge::~HalfEdge() {}

const HalfEdgeMesh::HalfEdge *HalfEdgeMesh::HalfEdge::Prev() const {
  const HalfEdgeMesh::HalfEdge *aThis = this;

  while (aThis) {
    if (aThis->Next() == this)
      return aThis;

    aThis = aThis->Next();
  }

  return nullptr;
}

/* HalfEdgeMesh::Face */

HalfEdgeMesh::Face::Face() : myOuterEdge(), myNormal(), myId(-1) {}

HalfEdgeMesh::Face::Face(HalfEdge *theOuterEdge)
    : myOuterEdge(theOuterEdge), myNormal(0., 0., 0.), myId(-1) {}

HalfEdgeMesh::Face::Face(Face &&theOther) noexcept {
  myOuterEdge = theOther.myOuterEdge;
  theOther.myOuterEdge = nullptr;
  myNormal = std::move(theOther.myNormal);
  myId = theOther.myId;
}

HalfEdgeMesh::Face &HalfEdgeMesh::Face::operator=(Face &&theOther) noexcept {
  myOuterEdge = theOther.myOuterEdge;
  theOther.myOuterEdge = nullptr;
  myNormal = std::move(theOther.myNormal);
  myId = theOther.myId;

  return *this;
}

HalfEdgeMesh::Face::~Face() {}

/* HalfEdgeMesh::Face::EdgeIterator */

HalfEdgeMesh::Face::EdgeIterator::EdgeIterator(const Face *theFace) {
  myOwner = theFace;
  myCurrent = theFace->myOuterEdge;
  myFirstTime = true;
}

Naive_Bool HalfEdgeMesh::Face::EdgeIterator::More() const {
  if (myCurrent == nullptr) {
    return false;
  }

  if (myFirstTime) {
    myFirstTime = false;
    return true;
  }

  if (myCurrent == myOwner->myOuterEdge) {
    return false;
  }

  return true;
}

/* HalfEdgeMesh */

HalfEdgeMesh::HalfEdgeMesh()
    : myVertexIndex(0), myFaceIndex(0), myVertexSlots(), myFaceSlots(),
      myVertices(), myHalfEdges(), myFaces(), myIsValid(false) {}

HalfEdgeMesh::HalfEdgeMesh(const TriangleSoup &theTriangleSoup)
    : myVertexIndex(0), myFaceIndex(0), myVertexSlots(), myFaceSlots(),
      myVertices(), myHalfEdges(), myFaces(), myIsValid(false) {
  for (const Naive_Point3d &aVertex : theTriangleSoup.Vertices()) {
    AddVertex(aVertex);
  }

  for (const Naive_Triangle &aTriangle : theTriangleSoup.Triangles()) {
    if (AddFace(aTriangle(0), aTriangle(1), aTriangle(2)) < 0)
      return;
  }

  myIsValid = true;
}

HalfEdgeMesh::~HalfEdgeMesh() {}

const HalfEdgeMesh::Vertex *HalfEdgeMesh::GetVertex(Naive_Integer theId) const {
  auto ret = myVertices.find(theId);

  if (ret == myVertices.end())
    return nullptr;

  return &ret->second;
}

const HalfEdgeMesh::HalfEdge *
HalfEdgeMesh::GetHalfEdge(const HalfEdgeId &theId) const {
  auto ret = myHalfEdges.find(theId);

  if (ret == myHalfEdges.end())
    return nullptr;

  return &ret->second;
}

const HalfEdgeMesh::Face *HalfEdgeMesh::GetFace(Naive_Integer theId) const {
  auto ret = myFaces.find(theId);

  if (ret == myFaces.end())
    return nullptr;

  return &ret->second;
}

Naive_Bool HalfEdgeMesh::addVertex(Naive_Integer theId,
                                   const Naive_Point3d &thePoint) {
  Vertex anVertex{thePoint};
  anVertex.myId = theId;
  auto result = myVertices.emplace(theId, std::move(anVertex));

  return result.second;
}

Naive_Integer HalfEdgeMesh::AddVertex(const Naive_Point3d &thePoint) {
  Naive_Integer anId = myVertexIndex;

  if (myVertexSlots.empty()) {
    if (addVertex(anId, thePoint))
      myVertexIndex++;
  } else {
    anId = myVertexSlots.top();

    if (addVertex(anId, thePoint))
      myVertexSlots.pop();
  }

  return anId;
}

Naive_Integer HalfEdgeMesh::AddFace(Naive_Integer theV1, Naive_Integer theV2,
                                    Naive_Integer theV3) {
  /* If there are duplicate points, quit. */

  if (theV1 == theV2 || theV2 == theV3 || theV3 == theV1)
    return -1;

  /* If any point is not found, quit. */

  if (myVertices.find(theV1) == myVertices.end())
    return -1;

  if (myVertices.find(theV2) == myVertices.end())
    return -1;

  if (myVertices.find(theV3) == myVertices.end())
    return -1;

  HalfEdgeId anEdgeId1{theV1, theV2};
  HalfEdgeId anEdgeId2{theV2, theV3};
  HalfEdgeId anEdgeId3{theV3, theV1};

  /* If the mesh contains the edge already, quit. */

  if (myHalfEdges.find(anEdgeId1) != myHalfEdges.end())
    return -1;

  if (myHalfEdges.find(anEdgeId2) != myHalfEdges.end())
    return -1;

  if (myHalfEdges.find(anEdgeId3) != myHalfEdges.end())
    return -1;

  Vertex *anV1 = &myVertices[theV1];
  Vertex *anV2 = &myVertices[theV2];
  Vertex *anV3 = &myVertices[theV3];

  auto edgeRet1 = myHalfEdges.emplace(anEdgeId1, HalfEdge{anV1, anV2});
  auto edgeRet2 = myHalfEdges.emplace(anEdgeId2, HalfEdge{anV2, anV3});
  auto edgeRet3 = myHalfEdges.emplace(anEdgeId3, HalfEdge{anV3, anV1});

  HalfEdge *anEdge1 = &edgeRet1.first->second;
  HalfEdge *anEdge2 = &edgeRet2.first->second;
  HalfEdge *anEdge3 = &edgeRet3.first->second;

  /* If a vertex has no edge, register it. */

  if (anV1->myEdge == nullptr)
    anV1->myEdge = anEdge1;

  if (anV2->myEdge == nullptr)
    anV2->myEdge = anEdge2;

  if (anV3->myEdge == nullptr)
    anV3->myEdge = anEdge3;

  /* Set the origin of the edges. */

  anEdge1->myOrigin = anV1;
  anEdge2->myOrigin = anV2;
  anEdge3->myOrigin = anV3;

  /* Set the next edge of the edges. */

  anEdge1->myNext = anEdge2;
  anEdge2->myNext = anEdge3;
  anEdge3->myNext = anEdge1;

  /* Find twin edge and register it. */

  auto twin1 = myHalfEdges.find(anEdgeId1.Twin());
  if (twin1 != myHalfEdges.end()) {
    HalfEdge *anTwin = &twin1->second;
    anEdge1->myTwin = anTwin;
    anTwin->myTwin = anEdge1;
  }

  auto twin2 = myHalfEdges.find(anEdgeId2.Twin());
  if (twin2 != myHalfEdges.end()) {
    HalfEdge *anTwin = &twin2->second;
    anEdge2->myTwin = anTwin;
    anTwin->myTwin = anEdge2;
  }

  auto twin3 = myHalfEdges.find(anEdgeId3.Twin());
  if (twin3 != myHalfEdges.end()) {
    HalfEdge *anTwin = &twin3->second;
    anEdge3->myTwin = anTwin;
    anTwin->myTwin = anEdge3;
  }

  /* Insert the face. */

  Naive_Integer anFaceId = myFaceIndex;
  Face *anFace = nullptr;

  if (myFaceSlots.empty()) {
    auto faceRet = myFaces.emplace(anFaceId, Face{anEdge1});
    anFace = &faceRet.first->second;
  } else {
    anFaceId = myFaceSlots.top();
    auto faceRet = myFaces.emplace(anFaceId, Face{anEdge1});
    anFace = &faceRet.first->second;
    myFaceSlots.pop();
  }

  /* Set the ID of the face. */

  anFace->myId = anFaceId;

  /* Set the face of the edges. */

  anEdge1->myFace = anFace;
  anEdge2->myFace = anFace;
  anEdge3->myFace = anFace;

  return anFaceId;
}

Naive_Bool HalfEdgeMesh::RemoveVertex(Naive_Integer theId) {
  auto itVert = myVertices.find(theId);

  if (itVert == myVertices.end())
    return false;

  const Vertex *anVertex = &itVert->second;

  const HalfEdge *anEdge = anVertex->myEdge;

  if (!anEdge) {
    // myVertices.
  }

  return true;
}

Naive_EXPORT Naive_Bool HalfEdgeMesh::RemoveFace(Naive_Integer theId) {
  return false;
}

Naive_NAMESPACE_END(geometry);
