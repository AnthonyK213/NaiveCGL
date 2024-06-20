#include <naivecgl/Geometry/HalfEdgeMesh.h>

#include <set>
#include <tuple>

Naive_NAMESPACE_BEGIN(geometry);

/* HalfEdgeMesh::HalfEdgeId */

HalfEdgeMesh::HalfEdgeId::HalfEdgeId() : myA(-1), myB(-1) {}

HalfEdgeMesh::HalfEdgeId::HalfEdgeId(const VertexId theA, const VertexId theB)
    : myA(theA), myB(theB) {}

const HalfEdgeMesh::HalfEdgeId &HalfEdgeMesh::HalfEdgeId::Unset() {
  static HalfEdgeMesh::HalfEdgeId anId{};
  return anId;
}

Naive_Bool HalfEdgeMesh::HalfEdgeId::IsValid() const {
  return myA >= 0 && myB >= 0;
}

Naive_Bool
HalfEdgeMesh::HalfEdgeId::operator!=(const HalfEdgeId &theOther) const {
  return myA != theOther.myA || myB != theOther.myB;
}

Naive_Bool
HalfEdgeMesh::HalfEdgeId::operator==(const HalfEdgeId &theOther) const {
  return myA == theOther.myA && myB == theOther.myB;
}

Naive_Bool
HalfEdgeMesh::HalfEdgeId::operator<(const HalfEdgeId &theOther) const {
  if (myA < theOther.myA) {
    return Naive_True;
  } else if (myA == theOther.myA) {
    return myB < theOther.myB;
  } else {
    return Naive_False;
  }
}

Naive_Bool
HalfEdgeMesh::HalfEdgeId::operator>(const HalfEdgeId &theOther) const {
  if (myA > theOther.myA) {
    return Naive_True;
  } else if (myA == theOther.myA) {
    return myB > theOther.myB;
  } else {
    return Naive_False;
  }
}

Naive_Bool
HalfEdgeMesh::HalfEdgeId::operator<=(const HalfEdgeId &theOther) const {
  if (myA < theOther.myA) {
    return Naive_True;
  } else if (myA == theOther.myA) {
    return myB <= theOther.myB;
  } else {
    return Naive_False;
  }
}

Naive_Bool
HalfEdgeMesh::HalfEdgeId::operator>=(const HalfEdgeId &theOther) const {
  if (myA > theOther.myA) {
    return Naive_True;
  } else if (myA == theOther.myA) {
    return myB >= theOther.myB;
  } else {
    return Naive_False;
  }
}

/* HalfEdgeMesh::Vertex */

HalfEdgeMesh::Vertex::Vertex() : myCoord(), myEdge(), myId(-1) {}

HalfEdgeMesh::Vertex::Vertex(const Naive_Point3d &theCoord)
    : myCoord(theCoord), myEdge(), myId(-1) {}

HalfEdgeMesh::Vertex::Vertex(Naive_Real theX, Naive_Real theY, Naive_Real theZ)
    : myCoord(theX, theY, theZ), myEdge(), myId(-1) {}

/* HalfEdgeMesh::HalfEdge */

HalfEdgeMesh::HalfEdge::HalfEdge()
    : myOrigin(-1), myFace(-1), myTwin(), myPrev(), myNext(), myId() {}

HalfEdgeMesh::HalfEdge::HalfEdge(const VertexId theOrigin,
                                 const VertexId theNext)
    : myOrigin(theOrigin), myFace(-1), myTwin(), myPrev(), myNext(),
      myId(theOrigin, theNext) {}

/* HalfEdgeMesh::Face */

HalfEdgeMesh::Face::Face() : myOuterEdge(), myNormal(), myId(-1) {}

HalfEdgeMesh::Face::Face(const HalfEdgeId theOuterEdge)
    : myOuterEdge(theOuterEdge), myNormal(0., 0., 0.), myId(-1) {}

/* HalfEdgeMesh::Face::EdgeIterator */

HalfEdgeMesh::EdgeIterator::EdgeIterator(const HalfEdgeMesh &theMesh,
                                         const FaceId theFace)
    : myMesh(&theMesh), myCurrent() {
  myOwner = myMesh->GetFace(theFace);
  if (myOwner)
    myCurrent = myOwner->Edge();
  myFirstTime = Naive_True;
}

Naive_Bool HalfEdgeMesh::EdgeIterator::More() const {
  if (!myOwner || !myCurrent.IsValid())
    return Naive_False;

  if (myFirstTime) {
    myFirstTime = Naive_False;
    return Naive_True;
  }

  return myCurrent != myOwner->Edge();
}

void HalfEdgeMesh::EdgeIterator::Next() {
  const HalfEdge *anCrt = myMesh->GetHalfEdge(myCurrent);
  if (anCrt)
    myCurrent = anCrt->Next();
}

/* HalfEdgeMesh */

HalfEdgeMesh::HalfEdgeMesh()
    : myVertexIndex(0), myFaceIndex(0), myVertexSlots(), myFaceSlots(),
      myVertices(), myHalfEdges(), myFaces(), myIsValid(Naive_False) {}

HalfEdgeMesh::HalfEdgeMesh(const Naive_Poly &thePoly)
    : myVertexIndex(0), myFaceIndex(0), myVertexSlots(), myFaceSlots(),
      myVertices(), myHalfEdges(), myFaces(), myIsValid(Naive_False) {
  for (const Naive_Point3d &aVertex : thePoly.Vertices()) {
    AddVertex(aVertex);
  }

  for (const Naive_Triangle &aTriangle : thePoly.Triangles()) {
    if (AddFace(aTriangle(0), aTriangle(1), aTriangle(2)) < 0)
      return;
  }

  myIsValid = Naive_True;
}

const HalfEdgeMesh::Vertex *
HalfEdgeMesh::GetVertex(const VertexId theId) const {
  if (theId < 0)
    return nullptr;
  auto ret = myVertices.find(theId);
  return (ret == myVertices.end()) ? nullptr : &ret->second;
}

const HalfEdgeMesh::HalfEdge *
HalfEdgeMesh::GetHalfEdge(const HalfEdgeId theId) const {
  if (!theId.IsValid())
    return nullptr;
  auto ret = myHalfEdges.find(theId);
  return (ret == myHalfEdges.end()) ? nullptr : &ret->second;
}

const HalfEdgeMesh::Face *HalfEdgeMesh::GetFace(const FaceId theId) const {
  if (theId < 0)
    return nullptr;
  auto ret = myFaces.find(theId);
  return (ret == myFaces.end()) ? nullptr : &ret->second;
}

Naive_IntegerList HalfEdgeMesh::GetAllVertices() const {
  if (!IsValid())
    return {};

  Naive_IntegerList anIdList{};
  anIdList.reserve(NbVertices());

  for (auto anIter = myVertices.cbegin(); anIter != myVertices.cend();
       ++anIter) {
    anIdList.push_back(anIter->first);
  }

  return anIdList;
}

Naive_IntegerList HalfEdgeMesh::GetAllFaces() const {
  if (!IsValid())
    return {};

  Naive_IntegerList anIdList{};
  anIdList.reserve(NbFaces());

  for (auto anIter = myFaces.cbegin(); anIter != myFaces.cend(); ++anIter) {
    anIdList.push_back(anIter->first);
  }

  return anIdList;
}

Handle_Naive_Poly HalfEdgeMesh::Soup(Naive_Bool theCompat) const {
  if (!IsValid())
    return nullptr;

  Naive_Point3dList aVertices{};
  Naive_List<Naive_Triangle> aTriangles{};

  aVertices.reserve(NbVertices());
  aTriangles.reserve(NbFaces());

  Naive_Map<Naive_Integer, Naive_Integer> aVertIdMap{};
  Naive_Integer anIndex = 0;

  for (auto anIter = myVertices.cbegin(); anIter != myVertices.cend();
       ++anIter) {
    const Vertex &aVertex = anIter->second;

    if (theCompat && !aVertex.Edge().IsValid())
      continue;

    aVertices.push_back(aVertex.Coord());
    aVertIdMap.emplace(aVertex.Id(), anIndex);
    anIndex++;
  }

  for (auto anIter = myFaces.cbegin(); anIter != myFaces.cend(); ++anIter) {
    const Face &aFace = anIter->second;
    Naive_Triangle aTriangle{0, 0, 0};
    Naive_Integer anIdx = 0;

    for (auto itEdge = EdgeIter(aFace.Id()); itEdge.More(); itEdge.Next()) {
      // TODO: Ngon?
      if (anIdx >= 3)
        return nullptr;

      const HalfEdge *crtEdge = GetHalfEdge(itEdge.Current());
      auto ret = aVertIdMap.find(crtEdge->Origin());
      if (ret == aVertIdMap.end())
        return nullptr;

      aTriangle(anIdx) = ret->second;
      anIdx++;
    }

    aTriangles.push_back(aTriangle);
  }

  return new Naive_Poly(::std::move(aVertices), ::std::move(aTriangles));
}

Naive_Bool HalfEdgeMesh::addVertex(const VertexId theId,
                                   const Naive_Point3d &thePoint) {
  Vertex anVertex{thePoint};
  anVertex.myId = theId;
  auto result = myVertices.emplace(theId, ::std::move(anVertex));

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

Naive_Bool HalfEdgeMesh::RemoveVertex(const VertexId theId) {
  const Vertex *aVertex = GetVertex(theId);

  if (!aVertex)
    return Naive_False;

  const HalfEdge *aPrev = GetHalfEdge(aVertex->myEdge);
  const HalfEdgeId aNextId = aVertex->myEdge.Twin();

  do {
    if (!aPrev)
      break;

    FaceId aFaceId = aPrev->Owner();
    aPrev = GetHalfEdge(aPrev->Prev().Twin());
    RemoveFace(aFaceId);
  } while (GetHalfEdge(aVertex->myEdge));

  const HalfEdge *aNext = GetHalfEdge(aNextId);

  do {
    if (!aNext)
      break;

    FaceId aFaceId = aNext->Owner();
    aNext = GetHalfEdge(aNext->Next().Twin());
    RemoveFace(aFaceId);
  } while (GetHalfEdge(aVertex->myEdge));

  myVertices.erase(theId);
  myVertexSlots.push(theId);

  return Naive_True;
}

HalfEdgeMesh::FaceId HalfEdgeMesh::AddFace(const VertexId theV1,
                                           const VertexId theV2,
                                           const VertexId theV3) {
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

  auto edgeRet1 =
      myHalfEdges.emplace(anEdgeId1, HalfEdge{anV1->Id(), anV2->Id()});
  auto edgeRet2 =
      myHalfEdges.emplace(anEdgeId2, HalfEdge{anV2->Id(), anV3->Id()});
  auto edgeRet3 =
      myHalfEdges.emplace(anEdgeId3, HalfEdge{anV3->Id(), anV1->Id()});

  HalfEdge *anEdge1 = &edgeRet1.first->second;
  HalfEdge *anEdge2 = &edgeRet2.first->second;
  HalfEdge *anEdge3 = &edgeRet3.first->second;

  /* If a vertex has no edge, register it. */

  if (!GetHalfEdge(anV1->myEdge))
    anV1->myEdge = anEdge1->Id();

  if (!GetHalfEdge(anV2->myEdge))
    anV2->myEdge = anEdge2->Id();

  if (!GetHalfEdge(anV3->myEdge))
    anV3->myEdge = anEdge3->Id();

  /* Set the origin of the edges. */

  anEdge1->myOrigin = anV1->Id();
  anEdge2->myOrigin = anV2->Id();
  anEdge3->myOrigin = anV3->Id();

  /* Set the previous edge of the edges. */

  anEdge1->myPrev = anEdge3->Id();
  anEdge2->myPrev = anEdge1->Id();
  anEdge3->myPrev = anEdge2->Id();

  /* Set the next edge of the edges. */

  anEdge1->myNext = anEdge2->Id();
  anEdge2->myNext = anEdge3->Id();
  anEdge3->myNext = anEdge1->Id();

  /* Find twin edge and register it. */

  auto twin1 = myHalfEdges.find(anEdgeId1.Twin());
  if (twin1 != myHalfEdges.end()) {
    HalfEdge *anTwin = &twin1->second;
    anEdge1->myTwin = anTwin->Id();
    anTwin->myTwin = anEdge1->Id();
  }

  auto twin2 = myHalfEdges.find(anEdgeId2.Twin());
  if (twin2 != myHalfEdges.end()) {
    HalfEdge *anTwin = &twin2->second;
    anEdge2->myTwin = anTwin->Id();
    anTwin->myTwin = anEdge2->Id();
  }

  auto twin3 = myHalfEdges.find(anEdgeId3.Twin());
  if (twin3 != myHalfEdges.end()) {
    HalfEdge *anTwin = &twin3->second;
    anEdge3->myTwin = anTwin->Id();
    anTwin->myTwin = anEdge3->Id();
  }

  /* Insert the face. */

  Naive_Integer anFaceId = myFaceIndex;
  Face *anFace = nullptr;

  if (myFaceSlots.empty()) {
    auto faceRet = myFaces.emplace(anFaceId, Face{anEdge1->Id()});
    anFace = &faceRet.first->second;
    myFaceIndex++;
  } else {
    anFaceId = myFaceSlots.top();
    auto faceRet = myFaces.emplace(anFaceId, Face{anEdge1->Id()});
    anFace = &faceRet.first->second;
    myFaceSlots.pop();
  }

  /* Set the ID of the face. */

  anFace->myId = anFaceId;

  /* Set the face of the edges. */

  anEdge1->myFace = anFace->Id();
  anEdge2->myFace = anFace->Id();
  anEdge3->myFace = anFace->Id();

  return anFaceId;
}

Naive_Bool HalfEdgeMesh::removeHalfEdge(const HalfEdge *theEdge,
                                        Naive_Bool theCompat) {
  if (!theEdge)
    return Naive_False;

  Vertex *anOrigin = const_cast<Vertex *>(GetVertex(theEdge->myOrigin));

  /* To find anther edge for |anOrigin|... */

  if (anOrigin->myEdge == theEdge->Id()) {
    anOrigin->myEdge = HalfEdgeId::Unset();

    const HalfEdge *e = GetHalfEdge(theEdge->myTwin);
    if (e) {
      anOrigin->myEdge = e->myNext;
    }

    e = GetHalfEdge(theEdge->myPrev);
    if (!anOrigin->myEdge.IsValid() && e) {
      anOrigin->myEdge = e->myTwin;
    }

    if (!anOrigin->myEdge.IsValid()) {
      // FIXME: What if the mesh became non-manifold after deleting the face?
      //  Here!
      //    |
      // |\ v /|
      // | \ / |
      // | / \ |
      // |/   \|

      if (theCompat) {
        myVertexSlots.push(anOrigin->Id());
        myVertices.erase(anOrigin->Id());
      }
    }
  }

  HalfEdge *e;

  e = const_cast<HalfEdge *>(GetHalfEdge(theEdge->myTwin));
  if (e)
    e->myTwin = HalfEdgeId::Unset();

  e = const_cast<HalfEdge *>(GetHalfEdge(theEdge->myNext));
  if (e)
    e->myPrev = HalfEdgeId::Unset();

  e = const_cast<HalfEdge *>(GetHalfEdge(theEdge->myPrev));
  if (e)
    e->myNext = HalfEdgeId::Unset();

  myHalfEdges.erase(theEdge->Id());

  return Naive_True;
}

Naive_Bool HalfEdgeMesh::RemoveFace(const FaceId theId, Naive_Bool theCompat) {
  const Face *aFace = GetFace(theId);

  if (!aFace)
    return Naive_False;

  const HalfEdge *anEdge = GetHalfEdge(aFace->myOuterEdge);

  while (anEdge) {
    HalfEdge *anEdgeNext = const_cast<HalfEdge *>(GetHalfEdge(anEdge->myNext));
    removeHalfEdge(anEdge, theCompat);
    anEdge = anEdgeNext;
  }

  myFaces.erase(theId);
  myFaceSlots.push(theId);

  return Naive_True;
}

Naive_NAMESPACE_END(geometry);
