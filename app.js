// StayNear Web Application Engine (Bhimtal, Uttarakhand Edition)

// Initial Data matching C++ OOP Data Structures (Person -> Student, Owner, Room, PG)
const initialPgs = [
    {
        id: 1,
        pgName: "Himalayan Heights Student PG",
        collegeName: "Graphic Era Hill University Bhimtal",
        location: "June Estate, Bhimtal, Uttarakhand",
        pgType: "Boys",
        rent: 5500,
        rating: 4.8,
        owner: {
            name: "Rajesh Sharma",
            phone: "+91 98765 43210",
            email: "rajesh.sharma@staynear.com"
        },
        rooms: [
            {
                roomNumber: 101,
                totalBeds: 2,
                occupiedBeds: 1,
                students: [
                    { name: "Aarav Mehta", course: "B.Tech CSE", year: 2, phone: "+91 91234 56789" }
                ]
            },
            {
                roomNumber: 102,
                totalBeds: 3,
                occupiedBeds: 2,
                students: [
                    { name: "Rohan Verma", course: "BCA", year: 1, phone: "+91 98111 22334" },
                    { name: "Karan Joshi", course: "B.Tech ECE", year: 3, phone: "+91 97222 33445" }
                ]
            }
        ]
    },
    {
        id: 2,
        pgName: "Lake View Girls Haven",
        collegeName: "Graphic Era Hill University Bhimtal",
        location: "Bhowali Road, Near GEHU Gate, Bhimtal",
        pgType: "Girls",
        rent: 6200,
        rating: 4.9,
        owner: {
            name: "Sunita Pandey",
            phone: "+91 94120 88776",
            email: "sunita.pandey@staynear.com"
        },
        rooms: [
            {
                roomNumber: 201,
                totalBeds: 2,
                occupiedBeds: 1,
                students: [
                    { name: "Ananya Bisht", course: "B.Tech CSE", year: 1, phone: "+91 88990 11223" }
                ]
            },
            {
                roomNumber: 202,
                totalBeds: 2,
                occupiedBeds: 0,
                students: []
            }
        ]
    },
    {
        id: 3,
        pgName: "Pine Crest Scholar Stay",
        collegeName: "Birla Institute of Applied Sciences (BIAS) Bhimtal",
        location: "Tallital, Bhimtal, Uttarakhand",
        pgType: "Boys",
        rent: 4800,
        rating: 4.5,
        owner: {
            name: "Deepak Rawat",
            phone: "+91 97600 54321",
            email: "deepak.rawat@staynear.com"
        },
        rooms: [
            {
                roomNumber: 301,
                totalBeds: 2,
                occupiedBeds: 2,
                students: [
                    { name: "Vikas Negi", course: "MCA", year: 2, phone: "+91 99887 76655" },
                    { name: "Priya Ranjan", course: "B.Tech ME", year: 4, phone: "+91 94567 89012" }
                ]
            }
        ]
    }
];

// App State
let pgs = JSON.parse(localStorage.getItem('staynear_pgs')) || initialPgs;

// DOM Elements
const pgGrid = document.getElementById('pgGrid');
const searchInput = document.getElementById('searchInput');
const searchBtn = document.getElementById('searchBtn');
const typeFilter = document.getElementById('typeFilter');
const budgetRange = document.getElementById('budgetRange');
const budgetValue = document.getElementById('budgetValue');
const onlyAvailableCheck = document.getElementById('onlyAvailableCheck');
const resultsCount = document.getElementById('resultsCount');

// Stats Elements
const statTotalPgs = document.getElementById('statTotalPgs');
const statAvailableBeds = document.getElementById('statAvailableBeds');

// Modal Elements
const openAddPgBtn = document.getElementById('openAddPgBtn');
const addPgModal = document.getElementById('addPgModal');
const closeAddPgModal = document.getElementById('closeAddPgModal');
const cancelAddPgBtn = document.getElementById('cancelAddPgBtn');
const addPgForm = document.getElementById('addPgForm');

const viewPgModal = document.getElementById('viewPgModal');
const closeViewPgModal = document.getElementById('closeViewPgModal');
const viewPgTitle = document.getElementById('viewPgTitle');
const viewPgBody = document.getElementById('viewPgBody');

// Helper: Calculate total available beds for a PG
function getAvailableBedsCount(pg) {
    return pg.rooms.reduce((acc, r) => acc + (r.totalBeds - r.occupiedBeds), 0);
}

// Save state to LocalStorage
function saveState() {
    localStorage.setItem('staynear_pgs', JSON.stringify(pgs));
}

// Update Statistics Header
function updateStats() {
    statTotalPgs.textContent = pgs.length;
    const totalAvailable = pgs.reduce((acc, pg) => acc + getAvailableBedsCount(pg), 0);
    statAvailableBeds.textContent = totalAvailable;
}

// Render PG Grid
function renderPgs() {
    const query = searchInput.value.toLowerCase().trim();
    const selectedType = typeFilter.value;
    const maxBudget = parseInt(budgetRange.value, 10);
    const onlyAvailable = onlyAvailableCheck.checked;

    const filtered = pgs.filter(pg => {
        const matchesQuery = pg.pgName.toLowerCase().includes(query) || 
                             pg.collegeName.toLowerCase().includes(query) ||
                             pg.location.toLowerCase().includes(query);
        const matchesType = (selectedType === 'all') || (pg.pgType === selectedType);
        const matchesBudget = pg.rent <= maxBudget;
        const availableBeds = getAvailableBedsCount(pg);
        const matchesAvailability = !onlyAvailable || (availableBeds > 0);

        return matchesQuery && matchesType && matchesBudget && matchesAvailability;
    });

    resultsCount.textContent = `Showing ${filtered.length} of ${pgs.length} registered PGs`;

    if (filtered.length === 0) {
        pgGrid.innerHTML = `
            <div style="grid-column: 1/-1; text-align: center; padding: 60px 20px; color: var(--text-muted);">
                <span style="font-size: 3rem;">❌</span>
                <h3 style="margin-top: 12px; color: #fff;">No PGs found matching your search criteria</h3>
                <p>Try adjusting your search query or increasing your maximum budget limit.</p>
            </div>
        `;
        return;
    }

    pgGrid.innerHTML = filtered.map(pg => {
        const availableBeds = getAvailableBedsCount(pg);
        const typeClass = pg.pgType.toLowerCase();

        return `
            <div class="pg-card">
                <div class="card-header-banner">
                    <div class="badge-group">
                        <span class="pg-type-badge ${typeClass}">${pg.pgType} PG</span>
                        <span class="rating-badge">⭐ ${pg.rating.toFixed(1)}</span>
                    </div>
                    <h3 class="pg-card-title">${pg.pgName}</h3>
                    <p class="pg-card-college">🎓 Near ${pg.collegeName}</p>
                </div>
                <div class="card-body">
                    <div class="info-row">
                        <span>📍 Location</span>
                        <strong>${pg.location}</strong>
                    </div>
                    <div class="info-row">
                        <span>💰 Monthly Rent</span>
                        <span class="rent-price">₹${pg.rent.toLocaleString()}</span>
                    </div>
                    <div class="info-row">
                        <span>👤 Owner</span>
                        <strong>${pg.owner.name}</strong>
                    </div>
                    <div class="info-row">
                        <span>🛏️ Status</span>
                        <span class="availability-tag ${availableBeds > 0 ? 'available' : 'full'}">
                            ${availableBeds > 0 ? `🟢 ${availableBeds} Beds Available` : '🔴 Full Occupancy'}
                        </span>
                    </div>
                </div>
                <div class="card-footer">
                    <button class="btn btn-secondary" onclick="viewPgDetails(${pg.id})">Rooms</button>
                    <button class="btn btn-secondary" onclick="locateOnMap('${encodeURIComponent(pg.pgName + ' ' + pg.location)}')">📍 Map</button>
                    <button class="btn btn-primary" onclick="contactOwner('${pg.owner.name}', '${pg.owner.phone}')">📞 Call</button>
                </div>
            </div>
        `;
    }).join('');

    updateStats();
}

// Locate PG on Embedded Google Map
window.locateOnMap = function(query) {
    const mapFrame = document.getElementById('googleMapFrame');
    if (mapFrame) {
        mapFrame.src = `https://maps.google.com/maps?q=${query}&t=&z=15&ie=UTF8&iwloc=&output=embed`;
        document.getElementById('mapSection').scrollIntoView({ behavior: 'smooth' });
    }
};

// View PG Details Modal

window.viewPgDetails = function(pgId) {
    const pg = pgs.find(p => p.id === pgId);
    if (!pg) return;

    viewPgTitle.textContent = pg.pgName;
    
    const roomsHtml = pg.rooms.map(r => {
        const available = r.totalBeds - r.occupiedBeds;
        const studentsHtml = r.students.length > 0 
            ? r.students.map(s => `
                <div style="background: var(--dark-bg); padding: 8px 12px; border-radius: 6px; font-size: 0.85rem; margin-top: 6px;">
                    👤 <strong>${s.name}</strong> (${s.course}, Year ${s.year}) — 📱 ${s.phone}
                </div>
              `).join('')
            : '<p style="font-size: 0.85rem; color: var(--text-muted); margin-top: 6px;">No students currently residing in this room.</p>';

        return `
            <div style="background: var(--card-hover); padding: 16px; border-radius: 8px; margin-bottom: 12px;">
                <div style="display: flex; justify-content: space-between; align-items: center;">
                    <strong style="font-size: 1.05rem; color: #fff;">Room #${r.roomNumber}</strong>
                    <span style="font-size: 0.85rem; color: ${available > 0 ? '#34d399' : '#f87171'};">
                        ${available > 0 ? `🟢 ${available} Beds Free` : '🔴 Room Full'} (Total Beds: ${r.totalBeds})
                    </span>
                </div>
                <div style="margin-top: 10px;">
                    <span style="font-size: 0.8rem; color: var(--text-muted); text-transform: uppercase; font-weight: 700;">Resident Students:</span>
                    ${studentsHtml}
                </div>
            </div>
        `;
    }).join('');

    viewPgBody.innerHTML = `
        <div style="margin-bottom: 20px;">
            <p>📍 <strong>Location:</strong> ${pg.location} 
               <a href="https://www.google.com/maps/search/?api=1&query=${encodeURIComponent(pg.pgName + ' ' + pg.location)}" target="_blank" style="color: #38bdf8; text-decoration: underline; margin-left: 10px; font-weight: 600;">
                 🗺️ Open in Google Maps App
               </a>
            </p>
            <p>🎓 <strong>College:</strong> ${pg.collegeName}</p>
            <p>💰 <strong>Monthly Rent:</strong> ₹${pg.rent.toLocaleString()} / bed</p>
            <p>⭐ <strong>Rating:</strong> ${pg.rating} / 5.0</p>
        </div>


        <div style="background: rgba(2, 132, 199, 0.1); border: 1px solid rgba(56, 189, 248, 0.3); padding: 16px; border-radius: 8px; margin-bottom: 24px;">
            <h4 style="color: #38bdf8; margin-bottom: 6px;">👤 Owner Information (Base Person Class)</h4>
            <p style="font-size: 0.9rem;"><strong>Name:</strong> ${pg.owner.name}</p>
            <p style="font-size: 0.9rem;"><strong>Phone:</strong> ${pg.owner.phone}</p>
            <p style="font-size: 0.9rem;"><strong>Email:</strong> ${pg.owner.email}</p>
        </div>

        <h4 style="color: #fff; margin-bottom: 12px;">🛏️ Room Breakdown (${pg.rooms.length} Total Rooms)</h4>
        ${roomsHtml}
    `;

    viewPgModal.classList.add('active');
};

// Contact Owner helper
window.contactOwner = function(name, phone) {
    alert(`Contact Owner:\nName: ${name}\nPhone: ${phone}`);
};

// Event Listeners
searchInput.addEventListener('input', renderPgs);
typeFilter.addEventListener('change', renderPgs);
onlyAvailableCheck.addEventListener('change', renderPgs);
searchBtn.addEventListener('click', renderPgs);

budgetRange.addEventListener('input', (e) => {
    budgetValue.textContent = `₹${parseInt(e.target.value, 10).toLocaleString()}`;
    renderPgs();
});

// Modal Actions
openAddPgBtn.addEventListener('click', () => addPgModal.classList.add('active'));
closeAddPgModal.addEventListener('click', () => addPgModal.classList.remove('active'));
cancelAddPgBtn.addEventListener('click', () => addPgModal.classList.remove('active'));
closeViewPgModal.addEventListener('click', () => viewPgModal.classList.remove('active'));

// Close modal on background click
window.addEventListener('click', (e) => {
    if (e.target === addPgModal) addPgModal.classList.remove('active');
    if (e.target === viewPgModal) viewPgModal.classList.remove('active');
});

// Add PG Form Submit
addPgForm.addEventListener('submit', (e) => {
    e.preventDefault();

    const totalRms = parseInt(document.getElementById('totalRooms').value, 10);
    const bedsPerRm = parseInt(document.getElementById('bedsPerRoom').value, 10);

    const generatedRooms = [];
    for (let i = 1; i <= totalRms; i++) {
        generatedRooms.push({
            roomNumber: 100 + i,
            totalBeds: bedsPerRm,
            occupiedBeds: 0,
            students: []
        });
    }

    const newPg = {
        id: Date.now(),
        pgName: document.getElementById('pgName').value.trim(),
        collegeName: document.getElementById('collegeName').value.trim(),
        location: document.getElementById('location').value.trim(),
        pgType: document.getElementById('pgType').value,
        rent: parseInt(document.getElementById('rent').value, 10),
        rating: parseFloat(document.getElementById('rating').value),
        owner: {
            name: document.getElementById('ownerName').value.trim(),
            phone: document.getElementById('ownerPhone').value.trim(),
            email: document.getElementById('ownerEmail').value.trim()
        },
        rooms: generatedRooms
    };

    pgs.unshift(newPg);
    saveState();
    renderPgs();

    addPgForm.reset();
    addPgModal.classList.remove('active');
    alert('✅ New PG successfully registered in Bhimtal!');
});

// Initial Render
renderPgs();
