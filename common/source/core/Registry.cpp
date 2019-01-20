/*
 * =====================================================================================
 *
 *       Filename:  Registry.cpp
 *
 *    Description:
 *
 *        Created:  23/06/2018 22:43:56
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/core/Exception.hpp>

#include "Registry.hpp"

Registry *Registry::s_instance = nullptr;

Block &Registry::registerBlock(u32 textureID, const std::string &id, const std::string &name) {
	u32 internalID = m_blocks.size();
	m_blocksID.emplace(id, internalID);
	return m_blocks.emplace_back(internalID, textureID, id, name);
}

Item &Registry::registerItem(u32 textureID, const std::string &id, const std::string &name) {
	u32 internalID = m_items.size();
	m_itemsID.emplace(id, internalID);
	return m_items.emplace_back(internalID, textureID, id, name);
}

const Block &Registry::getBlock(const std::string &id) {
	if (id.empty()) return getBlock((int)0);
	auto it = m_blocksID.find(id);
	if (it == m_blocksID.end())
		throw EXCEPTION("Unknown block:", id);
	return getBlock(it->second);
}

const Item &Registry::getItem(const std::string &id) {
	if (id.empty()) return getItem((int)0);
	auto it = m_itemsID.find(id);
	if (it == m_itemsID.end())
		throw EXCEPTION("Unknown item:", id);
	return getItem(it->second);
}

const Recipe *Registry::getRecipe(const Inventory &inventory) const {
	for (auto &recipe : m_recipes) {
		if (recipe->isMatching(inventory))
			return recipe.get();
	}
	return nullptr;
}

void Registry::serialize(sf::Packet &packet) {
	for (auto &it : m_blocks) {
		packet << u8(DataType::Block) << u32(it.id()) << it.name() << it.label() << u8(it.drawType())
			<< it.textureID() << it.hardness() << it.harvestRequirements();
	}

	for (auto &it : m_items) {
		packet << u8(DataType::Item) << it.id() << it.name() << it.label()
			<< it.textureID() << it.isBlock() << it.isFuel()
			<< it.burnTime() << it.miningSpeed() << it.harvestCapability();
	}
}

void Registry::deserialize(sf::Packet &packet) {
	u8 type;
	u32 id, textureID;
	std::string name, label;
	while (!packet.endOfPacket()) {
		packet >> type;
		if (type == u8(DataType::Block)) {
			u8 harvestRequirements, drawType;
			float hardness;
			packet >> id >> name >> label >> drawType >> textureID >> hardness >> harvestRequirements;

			auto &block = registerBlock(textureID, name, label);
			block.setHarvestRequirements(harvestRequirements);
			block.setHardness(hardness);
			block.setDrawType(BlockDrawType(drawType));
		}
		else if (type == u8(DataType::Item)) {
			bool isFuel, isBlock;
			u8 harvestCapability;
			float miningSpeed;
			u16 burnTime;
			packet >> id >> name >> label >> textureID >> isBlock >> isFuel >> burnTime >> miningSpeed >> harvestCapability;

			auto &item = registerItem(textureID, name, label);
			item.setIsFuel(isFuel);
			item.setIsBlock(isBlock);
			item.setMiningSpeed(miningSpeed);
			item.setBurnTime(burnTime);
		}
		else if (type == u8(DataType::Recipe)) {
		}
	}
}

