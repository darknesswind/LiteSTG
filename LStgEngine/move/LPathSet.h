#ifndef __LPATHSET_H__
#define __LPATHSET_H__

namespace proto
{
	class EmptyNode;
	class LineNode;
	class SineNode;
}
class LPathNodes;
class LPathSet
{
public:
	LPathSet();
	~LPathSet();

	bool load(LPCWSTR lpFile);
	const LPathNodes* getPath(uint id);
	void clear();

private:
	void parse(LPathNodes* pPath, const proto::EmptyNode& node);
	void parse(LPathNodes* pPath, const proto::LineNode& node);
	void parse(LPathNodes* pPath, const proto::SineNode& node);


private:
	std::vector<LPathNodes*> m_paths;
};

#endif // __LPATHSET_H__
