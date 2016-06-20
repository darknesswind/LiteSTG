#pragma once

class LFixedAnimeCut
{
public:
	class Iterator
	{
		friend class LFixedAnimeCut;
		Iterator(LFixedAnimeCut* pAnimeCut);
	public:
		~Iterator() = default;
		void next();
		LGraphHandle graph() const { return m_curGraph; }

		LGraphHandle operator* () const { return graph(); }
		void operator++ () { next(); }

	private:
		uint m_curIdx = 0;
		uint m_counter = 0;
		LFixedAnimeCut* m_pAnimeCut;
		LGraphHandle m_curGraph;
	};

public:
	LFixedAnimeCut() = default;
	~LFixedAnimeCut() = default;

	void setLoopPos(uint pos) { m_loopPos = pos; }
	void setInterval(uint inv) { m_inteval = inv; }
	uint loopPos() const { return m_loopPos; }
	uint interval() const { return m_inteval; }

	void assign(const LGraphHandles& graphs) { m_graphs = graphs; }
	void assign(LGraphHandles&& graphs) { m_graphs = graphs; }
	uint size() const { return m_graphs.size(); }
	LGraphHandle getGraph(uint idx) const { return m_graphs[idx]; }

	Iterator&& createIterator() { return std::move(Iterator(this)); }

protected:
	uint m_loopPos	= 0;
	uint m_inteval	= 6;
	LGraphHandles m_graphs;
};

class LFixedAnime
{
public:
	LFixedAnime();
	~LFixedAnime() = default;

	bool changeState(uint state);

	uint registerState(const LFixedAnimeCut& cut) { m_states.push_back(cut); return m_states.size() - 1; }
	uint registerState(LFixedAnimeCut&& cut) { m_states.emplace_back(std::move(cut)); return m_states.size() - 1; }
	uint registerState() { m_states.emplace_back(LFixedAnimeCut()); return m_states.size() - 1; }
	LFixedAnimeCut& getState(uint state) { return m_states[state]; }

private:
	std::vector<LFixedAnimeCut> m_states;
	LFixedAnimeCut::Iterator m_iterator;
};