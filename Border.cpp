#include "Border.h"

using namespace std;

Border::Border(Vector2d position, int width, int height) : Collider(CollisionFlag::STATIC, position, width, height){
}

void Border::OnCollision(Collider* const other) {

}

Border::~Border() {
}
