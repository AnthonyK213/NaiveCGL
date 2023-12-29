#include <naivecgl/Geometry/HalfEdgeMesh.h>

#include <tuple>

Naive_Namespace_Begin(geometry);

HalfEdgeMesh::Vertex_::Vertex_() {}

HalfEdgeMesh::Vertex_::Vertex_(const Naive_Vector3d &theCoord)
    : myCoord(theCoord), myEdge(nullptr), myId(0) {}

HalfEdgeMesh::Vertex_::Vertex_(Naive_Real theX, Naive_Real theY,
                               Naive_Real theZ)
    : myCoord(theX, theY, theZ), myEdge(nullptr), myId(0) {}

HalfEdgeMesh::Vertex_::Vertex_(Vertex_ &&theOther) noexcept {
  myCoord = std::move(theOther.myCoord);
  myEdge = theOther.myEdge;
  theOther.myEdge = nullptr;
  myId = theOther.myId;
}

HalfEdgeMesh::Vertex_ &
HalfEdgeMesh::Vertex_::operator=(Vertex_ &&theOther) noexcept {
  myCoord = std::move(theOther.myCoord);
  myEdge = theOther.myEdge;
  theOther.myEdge = nullptr;
  myId = theOther.myId;

  return *this;
}

HalfEdgeMesh::Vertex_::~Vertex_() {}

HalfEdgeMesh::HalfEdge_::HalfEdge_() {}

HalfEdgeMesh::HalfEdge_::HalfEdge_(Vertex_ *theOrigin)
    : myOrigin(theOrigin), myTwin(nullptr), myFace(nullptr), myNext(nullptr),
      myId(0) {}

HalfEdgeMesh::HalfEdge_::HalfEdge_(HalfEdge_ &&theOther) noexcept {
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

HalfEdgeMesh::HalfEdge_ &
HalfEdgeMesh::HalfEdge_::operator=(HalfEdge_ &&theOther) noexcept {
  myOrigin = theOther.myOrigin;
  myTwin = theOther.myTwin;
  myFace = theOther.myFace;
  myNext = theOther.myNext;
  theOther.myOrigin = nullptr;
  theOther.myTwin = nullptr;
  theOther.myFace = nullptr;
  theOther.myNext = nullptr;
  myId = theOther.myId;

  return *this;
}

HalfEdgeMesh::HalfEdge_::~HalfEdge_() {}

HalfEdgeMesh::Face_::Face_() {}

HalfEdgeMesh::Face_::Face_(HalfEdge_ *theOuterEdge)
    : myOuterEdge(theOuterEdge), myNormal(0., 0., 0.), myId(0) {}

HalfEdgeMesh::Face_::Face_(Face_ &&theOther) noexcept {
  myOuterEdge = theOther.myOuterEdge;
  theOther.myOuterEdge = nullptr;
  myNormal = std::move(theOther.myNormal);
  myId = theOther.myId;
}

HalfEdgeMesh::Face_ &HalfEdgeMesh::Face_::operator=(Face_ &&theOther) noexcept {
  myOuterEdge = theOther.myOuterEdge;
  theOther.myOuterEdge = nullptr;
  myNormal = std::move(theOther.myNormal);
  myId = theOther.myId;

  return *this;
}

HalfEdgeMesh::Face_::~Face_() {}

HalfEdgeMesh::Face_::EdgeIterator::EdgeIterator(const Face_ *theFace) {
  myOwner = theFace;
  myCurrent = theFace->myOuterEdge;
  myFirstTime = true;
}

Naive_Bool HalfEdgeMesh::Face_::EdgeIterator::More() const {
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

HalfEdgeMesh::HalfEdgeMesh()
    : myVertexIndex(0), myHalfEdgeIndex(0), myFaceIndex(0) {}

HalfEdgeMesh::HalfEdgeMesh(const TriangleSoup &theTriangleSoup)
    : myVertexIndex(0), myHalfEdgeIndex(0), myFaceIndex(0) {
  /// Insert vertices.
  for (const Naive_Vector3d &aVertex : theTriangleSoup.Vertices()) {
    addVertex({aVertex});
  }

  /// Insert faces and their edges.
  /// Twins of the half-edges are not set yet.
  for (const Naive_Triangle &aTriangle : theTriangleSoup.Triangles()) {
    /// Vertex key starts from 1!
    HalfEdge_ &edge0 = addHalfEdge({&myVertices[aTriangle(0) + 1]});
    HalfEdge_ &edge1 = addHalfEdge({&myVertices[aTriangle(1) + 1]});
    HalfEdge_ &edge2 = addHalfEdge({&myVertices[aTriangle(2) + 1]});

    edge0.myNext = &edge1;
    edge1.myNext = &edge2;
    edge2.myNext = &edge0;

    /// TODO: Boundary check.
    edge0.myOrigin->myEdge = &edge0;
    edge1.myOrigin->myEdge = &edge1;
    edge2.myOrigin->myEdge = &edge2;

    Face_ &face = addFace({&edge0});

    /// Store face index in the boundary edges.
    edge0.myFace = &face;
    edge1.myFace = &face;
    edge2.myFace = &face;
  }

  makeTwins();
}

HalfEdgeMesh::~HalfEdgeMesh() {}

HalfEdgeMesh::Vertex_ &HalfEdgeMesh::addVertex(Vertex_ &&theVertex) {
  Naive_Integer id = ++myVertexIndex;
  myVertices.emplace(id, std::move(theVertex));
  Vertex_ &vert = myVertices[id];
  vert.myId = id;
  return vert;
}

HalfEdgeMesh::HalfEdge_ &HalfEdgeMesh::addHalfEdge(HalfEdge_ &&theHalfEdge) {
  Naive_Integer id = ++myHalfEdgeIndex;
  myHalfEdges.emplace(id, std::move(theHalfEdge));
  HalfEdge_ &edge = myHalfEdges[id];
  edge.myId = id;
  return edge;
}

HalfEdgeMesh::Face_ &HalfEdgeMesh::addFace(Face_ &&theFace) {
  Naive_Integer id = ++myFaceIndex;
  myFaces.emplace(id, std::move(theFace));
  Face_ &f = myFaces[id];
  f.myId = id;
  return f;
}

void HalfEdgeMesh::makeTwins() {
  /// Use an ordered map to find "duplicate" edges.
  /// Better solution?

  Naive_Map<std::tuple<Naive_Integer, Naive_Integer>, Naive_Integer> edgeMap{};

  for (auto anIter = myHalfEdges.cbegin(); anIter != myHalfEdges.cend();
       ++anIter) {
    Naive_Integer thisV = anIter->second.myOrigin->myId;
    Naive_Integer nextV = anIter->second.myNext->myOrigin->myId;

    /// The key is the index of the start and end vertex indices: (a, b),
    /// which a <= b.
    if (thisV > nextV)
      std::swap(thisV, nextV);

    std::tuple<Naive_Integer, Naive_Integer> tup{thisV, nextV};
    auto key = edgeMap.find(tup);

    /// If the edge is not in the `edgeMap`, just insert the pair.
    if (key == edgeMap.cend()) {
      edgeMap.emplace(tup, anIter->first);
      continue;
    }

    /// Finally find the "duplicate" edges, make them twins.
    HalfEdge_ *edge = &myHalfEdges[anIter->first];
    HalfEdge_ *theTwin = &myHalfEdges[key->second];
    theTwin->myTwin = edge;
    edge->myTwin = theTwin;
  }
}

Naive_Namespace_End(geometry);
