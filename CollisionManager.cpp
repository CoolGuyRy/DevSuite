#include "CollisionManager.h"

HashTable::HashTable(int size) : mSize(size) {
	mHashTable.resize(mSize);
}
void HashTable::Update(vector<sf::Sprite*> vec) {
	mHashTable.clear();
	mHashTable.resize(mSize);

	for (auto it = 0; it < vec.size(); it++) {
		Insert(vec.at(it));
	}
}
bool HashTable::Check(sf::Sprite* spr) {
	sf::Vector2f topLeft, topRight, bottomLeft, bottomRight;
	topLeft = spr->getPosition();
	topRight = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width * spr->getScale().x, spr->getPosition().y);
	bottomLeft = sf::Vector2f(spr->getPosition().x, spr->getPosition().y + spr->getTextureRect().height * spr->getScale().y);
	bottomRight = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width * spr->getScale().x, spr->getPosition().y + spr->getTextureRect().height * spr->getScale().y);

	int topLeftHash, topRightHash, bottomLeftHash, bottomRightHash;
	topLeftHash = ComputeHash(topLeft);
	topRightHash = ComputeHash(topRight);
	bottomLeftHash = ComputeHash(bottomLeft);
	bottomRightHash = ComputeHash(bottomRight);

	if (topLeftHash == topRightHash && topRightHash == bottomRightHash && bottomRightHash == bottomLeftHash) {
		for (auto it = mHashTable[topLeftHash].begin(); it != mHashTable[topLeftHash].end(); it++) {
			if ((*it) == spr) {
				continue;
			}

			if (spr->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
				return true;
			}
		}
		return false;
	}
	if (topLeftHash == bottomLeftHash && topRightHash == bottomRightHash) {
		for (auto it = mHashTable[topLeftHash].begin(); it != mHashTable[topLeftHash].end(); it++) {
			if ((*it) == spr) {
				continue;
			}

			if (spr->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
				return true;
			}
		}
		for (auto it = mHashTable[topRightHash].begin(); it != mHashTable[topRightHash].end(); it++) {
			if ((*it) == spr) {
				continue;
			}

			if (spr->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
				return true;
			}
		}
		return false;
	}
	if (topLeftHash == topRightHash && bottomLeftHash == bottomRightHash) {
		for (auto it = mHashTable[topLeftHash].begin(); it != mHashTable[topLeftHash].end(); it++) {
			if ((*it) == spr) {
				continue;
			}

			if (spr->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
				return true;
			}
		}
		for (auto it = mHashTable[bottomLeftHash].begin(); it != mHashTable[bottomLeftHash].end(); it++) {
			if ((*it) == spr) {
				continue;
			}

			if (spr->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
				return true;
			}
		}
		return false;
	}


	for (auto it = mHashTable[topLeftHash].begin(); it != mHashTable[topLeftHash].end(); it++) {
		if ((*it) == spr) {
			continue;
		}

		if (spr->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
			return true;
		}
	}
	for (auto it = mHashTable[topRightHash].begin(); it != mHashTable[topRightHash].end(); it++) {
		if ((*it) == spr) {
			continue;
		}

		if (spr->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
			return true;
		}
	}
	for (auto it = mHashTable[bottomLeftHash].begin(); it != mHashTable[bottomLeftHash].end(); it++) {
		if ((*it) == spr) {
			continue;
		}

		if (spr->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
			return true;
		}
	}
	for (auto it = mHashTable[bottomRightHash].begin(); it != mHashTable[bottomRightHash].end(); it++) {
		if ((*it) == spr) {
			continue;
		}

		if (spr->getGlobalBounds().intersects((*it)->getGlobalBounds())) {
			return true;
		}
	}
	return false;
}
bool HashTable::Check(sf::Vector2f v) {
	int pointHash = ComputeHash(v);
	for (auto it = mHashTable[pointHash].begin(); it != mHashTable[pointHash].end(); it++) {
		if ((*it)->getGlobalBounds().contains(v)) {
			return true;
		}
	}
	return false;
}
void HashTable::Insert(sf::Sprite* spr) {
	sf::Vector2f topLeft, topRight, bottomLeft, bottomRight;
	topLeft = spr->getPosition();
	topRight = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width * spr->getScale().x, spr->getPosition().y);
	bottomLeft = sf::Vector2f(spr->getPosition().x, spr->getPosition().y + spr->getTextureRect().height * spr->getScale().y);
	bottomRight = sf::Vector2f(spr->getPosition().x + spr->getTextureRect().width * spr->getScale().x, spr->getPosition().y + spr->getTextureRect().height * spr->getScale().y);

	int topLeftHash, topRightHash, bottomLeftHash, bottomRightHash;
	topLeftHash = ComputeHash(topLeft);
	topRightHash = ComputeHash(topRight);
	bottomLeftHash = ComputeHash(bottomLeft);
	bottomRightHash = ComputeHash(bottomRight);

	if (topLeftHash == topRightHash && topRightHash == bottomRightHash && bottomRightHash == bottomLeftHash) {
		mHashTable[topLeftHash].push_back(spr);
		return;
	}
	if (topLeftHash == bottomLeftHash && topRightHash == bottomRightHash) {
		mHashTable[topLeftHash].push_back(spr);
		mHashTable[topRightHash].push_back(spr);
		return;
	}
	if (topLeftHash == topRightHash && bottomLeftHash == bottomRightHash) {
		mHashTable[topLeftHash].push_back(spr);
		mHashTable[bottomLeftHash].push_back(spr);
		return;
	}

	mHashTable[topLeftHash].push_back(spr);
	mHashTable[topRightHash].push_back(spr);
	mHashTable[bottomLeftHash].push_back(spr);
	mHashTable[bottomRightHash].push_back(spr);
}
void HashTable::Remove(sf::Sprite* spr) {

}
void HashTable::DebugInfo() {
	for (unsigned i = 0; i < 16; i++) {
		cout << "mHashTable[" << i << "] size: " << mHashTable[i].size() << endl;
	}
}
int HashTable::ComputeHash(sf::Vector2f v) {
	return (static_cast<int>(v.x) % 1280) / 320 + (static_cast<int>(v.y) % 960) / 240 * 4;
}

CollisionManager::CollisionManager(World* w) : mWorld(w) {
	mHashTable = new HashTable(DIV_X * DIV_Y);
}

void CollisionManager::Update() {

}